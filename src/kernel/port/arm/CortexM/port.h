/*
 * @author  AuWwow
 * @github  https://github.com/AuWwow
 * @mail    vladdlav324@gmail.com
 * @file    port.h
 * @date    2026-03-16
 */
#ifndef _PORT_H_
#define _PORT_H_
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

#include "kernel_types.h"

// Port initialization (configuring SysTick, NVIC, etc.)
void Port_Init(void);

// Start the first task (transition from MSP to PSP)
void Port_StartFirstTask(void) __attribute__((noreturn));

// Switch the stack to the task stack (called from PendSV)
void Port_SwitchContext(void);

// Critical sections via BASEPRI (recommended for Cortex-M3/M4/M7)
#define OS_CRITICAL_BASEPRI

// Minimum and maximum priority for BASEPRI
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    0x20    // example

#endif  // _PORT_H_
