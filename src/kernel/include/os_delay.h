/*
 * @author  AuWwow
 * @github  https://github.com/AuWwow
 * @mail    vladdlav324@gmail.com
 * @file    os_delay.h
 * @date    2026-03-16
 */
#ifndef _OS_DELAY_H_
#define _OS_DELAY_H_
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
#include "kernel_types.h"

// Delay in ticks (blocks the task until the time expires)
void OS_Delay(TickType_t ticks);

// Delay until an absolute time (blocks the task until the specified tick count is reached)
void OS_DelayUntil(TickType_t * const previousWakeTime, TickType_t timeIncrement);

#endif  // _OS_DELAY_H_
