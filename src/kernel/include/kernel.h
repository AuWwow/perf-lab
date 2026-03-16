/*
 * @author  AuWwow
 * @github  https://github.com/AuWwow
 * @mail    vladdlav324@gmail.com
 * @file    kernel.h
 * @date    2026-03-16
 */
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
/*
 * @author  AuWwow
 * @github  https://github.com/AuWwow
 * @mail    vladdlav324@gmail.com
 * @file    kernel.h
 * @date    2026-03-16
 */
#ifndef _KERNEL_H_
#define _KERNEL_H_
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

#include "kernel_types.h"
#include "task.h"
#include "scheduler.h"
#include "critical.h"
#include "os_delay.h"
// #include "mutex.h"

#ifdef __cplusplus
extern "C" {
#endif

// Initializing the kernel (before the scheduler starts)
void OS_Init(void);

// Running the scheduler — control is transferred to the kernel
void OS_Start(void) __attribute__((noreturn));

// Immediate transfer of control to another task (cooperative yield)
void OS_Yield(void);

// Transition the current task to the waiting state (tick-based)
void OS_Delay(TickType_t ticks);

// Get the current value of the system tick
TickType_t OS_GetTickCount(void);

// Get a pointer to the current task (for debugging/logging)
TaskHandle_t OS_GetCurrentTask(void);

#ifdef __cplusplus
}
#endif

#endif /* _KERNEL_H_ */