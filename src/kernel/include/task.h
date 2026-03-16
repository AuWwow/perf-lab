/*
 * @author  AuWwow
 * @github  https://github.com/AuWwow
 * @mail    vladdlav324@gmail.com
 * @file    task.h
 * @date    2026-03-16
 */
#ifndef _TASK_H_
#define _TASK_H_
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

#include "kernel_types.h"

typedef void (*TaskFunction_t)(void *argument);

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
// Creating a static task (stack and TCB are passed externally)
TaskHandle_t OS_CreateTaskStatic(
    TaskFunction_t      function,
    const char*         name,
    uint32_t*           stack,
    uint32_t            stack_size_words,
    Priority_t          priority,
    void*               argument
);

// Get the name of the task (for debugging)
const char* OS_TaskGetName(TaskHandle_t task);

// Get the current state of the task
TaskState_t OS_TaskGetState(TaskHandle_t task);

// Get the used stack (for overflow checking)
uint32_t OS_TaskGetStackHighWaterMark(TaskHandle_t task);

#endif  // _TASK_H_
