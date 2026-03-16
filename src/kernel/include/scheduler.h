/*
 * @author  AuWwow
 * @github  https://github.com/AuWwow
 * @mail    vladdlav324@gmail.com
 * @file    scheduler.h
 * @date    2026-03-16
 */
#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
#include "kernel_types.h"

// Called from PendSV — selects and returns the next task
TaskHandle_t Scheduler_PickNextTask(void);

// Add a task to the ready list (usually called when creating a task or after Delay)
void Scheduler_AddReadyTask(TaskHandle_t task);

// Remove a task from the ready list
void Scheduler_RemoveReadyTask(TaskHandle_t task);

#endif  // _SCHEDULER_H_
