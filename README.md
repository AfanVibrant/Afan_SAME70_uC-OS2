* Introduction
  - Project Backgroud/项目背景
  - uC/OS-II Introduction/
* Development
  - Project Cross Compiling
  - Project debugging

# INTRODUCTION
Without permission, do not commit the code to uC/OS-II mainline.
## Project Backgroud 项目背景
This project provides a simple RT-Thread RTOS demo on Microchip SAME70Q21.
All Afan RTOS repositories(FreeRTOS/uC/OS-II/uC/OS-III/RT-Thread/ThreadX) all
shares the same BSP from repository <https://github.com/AfanVibrant/Afan_SAME70_BSP.git>.

You can use free tools to develop, compile and debug this project on Microchip
ATSAME70Q21(ARM Cortex-M7 Core) MCU.

Tools used for this project are as following (using Windows as example):
  - IDE: Eclipse IDE for Embedded C/C++ Developers with Version: 2021-03 (4.19.0).
  - Cross-compile Tool: xpack-arm-none-eabi-gcc-10.2.1-1.1-win32-x64.
  - Windows Build Tool: xpack-windows-build-tools-4.2.1-2-win32-x64.
  - Windows Debug Tool: xpack-openocd-0.11.0-1-win32-x64.
  - Hardware Debugger:  CMSIS-DAP Tools or J-Link.

Project Components:
  - BSP files of ATSAME70Q21 are configured and generated from <https://start.atmel.com/>.
  - Please download project BSP file from <https://github.com/AfanVibrant/Afan_SAME70_BSP.git>.
  - All projects (FreeRTOS/RT-Thread/ThreadX/uC-OS2/uC-OS3) share the same BSP project.
  - For this repository, is based on uC/OS-II. <https://github.com/xxx>.

## uC/OS-II Introduction
.

# DEVELOPMENT

So before you download this repo, please download SAME70 BSP from following link :
	<https://github.com/AfanVibrant/Afan_SAME70_BSP.git>.

## Project Cross-Compiling

Following these steps (using Windows10 for example):
  - Downloading Eclipse IDE for Embedded C/C++ Developers with Version: 2021-03.
  - Downloading Cross-compile Tool: xpack-arm-none-eabi-gcc-10.2.1-1.1-win32-x64.
  - Downloading Windows Build Tool: xpack-windows-build-tools-4.2.1-2-win32-x64.
  - Downloading Windows Debug Tool: xpack-openocd-0.11.0-1-win32-x64.
  - Unzip all needed tools as mentioned before.
  - From Help directory you can get more details of setting up development environments. 

## Project Debugging

Will update soon: