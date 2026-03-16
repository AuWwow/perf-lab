/*
 * @author  AuWwow
 * @github  https://github.com/AuWwow
 * @mail    vladdlav324@gmail.com
 * @file    mutex.h
 * @date    2026-03-16
 */
#ifndef _MUTEX_H_
#define _MUTEX_H_
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

typedef struct Mutex* MutexHandle_t;

MutexHandle_t OS_MutexCreateStatic(void);

void OS_MutexLock(MutexHandle_t mutex);
void OS_MutexUnlock(MutexHandle_t mutex);

#endif  // _MUTEX_H_
