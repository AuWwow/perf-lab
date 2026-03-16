/*
 * @author  AuWwow
 * @github  https://github.com/AuWwow
 * @mail    vladdlav324@gmail.com
 * @file    kernel_types.h
 * @date    2026-03-16
 */
#ifndef _KERNEL_TYPES_H_
#define _KERNEL_TYPES_H_

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
#include <stdint.h>
#include <stdbool.h>

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
typedef uint32_t TickType_t;
typedef uint8_t  Priority_t;        // 0 = самый высокий, 31 = самый низкий

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
typedef struct TaskControlBlock* TaskHandle_t;

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
typedef enum {
    TASK_READY,
    TASK_RUNNING,
    TASK_BLOCKED_DELAY,
    TASK_BLOCKED_MUTEX,
    TASK_SUSPENDED,
    TASK_DELETED
} TaskState_t;

#endif  // _KERNEL_TYPES_H_
