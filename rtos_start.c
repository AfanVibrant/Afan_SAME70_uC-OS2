/****************************************************************************
 * Afan SAME70 uC/OS-II rtos_start.c
 * Author : Afan Vibrant (AfanVibrant@outlook.com)
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#include <atmel_start.h>
#include <peripheral_clk_config.h>

#include "rtos_config.h"

#include "rtos.h"
#include "rtos_start.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const char *led_task_name = "led task";
static OS_STK led_thread_stk[LEDRUN_THREAD_STKSZ/4];

/****************************************************************************
 * Public Functions Prototypes
 ****************************************************************************/

/****************************************************************************
 * Private Functions Prototypes
 ****************************************************************************/

static void led_thread_entry(void *parameter);

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static void display_task_info(void)
{
  OS_TCB      *ptcb;
  OS_STK_DATA stk;

  ptcb    = &OSTCBTbl[0];

  printf("==================================================\r\n");
  printf("  Prio     Used    Free    Per      Taskname\r\n");

  while (ptcb != NULL)
  {
    OSTaskStkChk(ptcb->OSTCBPrio, &stk);
    printf("   %2d    %5d    %5d    %02d%%     %s\r\n",
          ptcb->OSTCBPrio, 
          stk.OSUsed,
          stk.OSFree, 
          (stk.OSUsed * 100) / (stk.OSUsed + stk.OSFree),
          ptcb->OSTCBTaskName);
    ptcb = ptcb->OSTCBPrev;
  }
}

/****************************************************************************
 * Name: led_thread_entry
 *
 * Description:
 *   Task for LED.
 *
 * Input Parameters:
 *   NONE.
 *
 * Returned Value:
 *   None.
 *
 ****************************************************************************/

static void led_thread_entry(void *parameter)
{
  (void)parameter;

#if (OS_TASK_STAT_EN > 0)
  OSStatInit();               /* Call this function in a task */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
  CPU_IntDisMeasMaxCurReset();
#endif

  while (1)
  {
    printf("led task run\r\n");
    display_task_info();
    rtos_task_delay_ms(500);
  }
}

/*
 * Example
 */
void uCos2_V293X_start(void)
{
  INT8U err;

  printf("uCos2 with LWIP demo run on SAME70Q21\r\n");

  Mem_Init();     /* Initialize Memory Management Module  */
  Math_Init();    /* Initialize Mathematical Module       */

  OS_CPU_SysTickInitFreq(CONF_CPU_FREQUENCY);   /* Initialize uC/OS-II periodic timer (SysTick).*/

  OSInit();       /* Initialize uC/OS-II.                  */
  CPU_Init();     /* Initialize CPU */
  
  if(OS_ERR_NONE == OSTaskCreate(led_thread_entry, NULL,
                                 &led_thread_stk[LEDRUN_THREAD_STKSZ/4 - 1],
                                 (rtos_thread_t)LEDRUN_THREAD_PRIO)) {
    OSTaskNameSet(LEDRUN_THREAD_PRIO, (INT8U *)led_task_name, &err);
  }

  /* Start multitasking (i.e. give control to uC/OS-II) */
  
  OSStart();
}
