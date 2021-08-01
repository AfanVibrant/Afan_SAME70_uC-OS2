/****************************************************************************
 * Afan SAME70 uC/OS-II port/rtos.h
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

#ifndef PORT_RTOS_H
#define PORT_RTOS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <cpu.h>
#include <os_cpu.h>
#include <ucos_ii.h>              /* uC/OS-II header file */

#include <stdbool.h>
#include <compiler.h>

#include "rtos_config.h"

#define rtos_irq_enter()         CPU_SR_ALLOC(); \
                                  OS_ENTER_CRITICAL(); \
                                  OSIntEnter(); \
                                  OS_EXIT_CRITICAL()

#define rtos_irq_exit()          OSIntExit()

#define rtos_task_delay(n)       OSTimeDly(n)

#if OS_CRITICAL_METHOD == 3u
#  define rtos_enter_critical()  OS_CPU_SR  cpu_sr = 0u; \
                                  OS_ENTER_CRITICAL()
#  define rtos_exit_critical()   OS_EXIT_CRITICAL()
#endif

typedef struct tag_rtos_mbox {
  OS_EVENT     *mbox;  /* Point to the mail box */
  void        **pmsg;  /* Point to the message start address */
} rtos_mbox_t;

typedef OS_EVENT       *rtos_sem_t;
typedef OS_EVENT       *rtos_mutex_t;
typedef INT8U           rtos_thread_t;
typedef OS_TMR         *rtos_timer_t;
typedef unsigned int   rtos_prot_t;

#define RTOS_TICK_PER_SECOND      OS_TICKS_PER_SEC
#define RTOS_USEC_PER_TICK        (1000000/RTOS_TICK_PER_SECOND)

#define rtos_task_delay(n)        OSTimeDly(n)
#define rtos_task_delay_ms(n)     rtos_task_delay(1000*n/RTOS_USEC_PER_TICK)
#define rtos_task_delay_us(n)     uint32_t tick = (n > RTOS_USEC_PER_TICK) ? \
                                                  (n + 1)/RTOS_USEC_PER_TICK : 1; \
                                  rtos_task_delay(tick)

#define RTOS_MBOX_NULL (OS_EVENT *)0
#define RTOS_SEM_NULL  (OS_EVENT *)0

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PORT_RTOS_H */
