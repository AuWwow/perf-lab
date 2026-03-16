/*
 * @author  AuWwow
 * @github  https://github.com/AuWwow
 * @mail    vladdlav324@gmail.com
 * @file    critical.h
 * @date    2026-03-16
 */
#ifndef _CRITICAL_H_
#define _CRITICAL_H_
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

// Enter the critical section (disable interrupts / raise BASEPRI)
void OS_EnterCritical(void);

// Exit the critical section (enable interrupts / lower BASEPRI)
void OS_ExitCritical(void);

// Enter/exit for ISRs (manage nesting count, but don't change interrupt state)
void OS_EnterISR(void);
void OS_ExitISR(void);

#endif  // _CRITICAL_H_
