#ifndef MCAL_TIMER_TIMER_INT_H_
#define MCAL_TIMER_TIMER_INT_H_

#include "../../LIB/std_types.h"

// ---------------------------------------- Enums ---------------------------------------- //

// Timers
typedef enum
{
    TIMER_TIMER0,
    TIMER_TIMER1,
    TIMER_TIMER2
} TIMER_ENUM_Timers;

// Timer Prescalers
typedef enum
{
    TIMER_PRESCALER_1 = 1,
    TIMER_PRESCALER_8,
    TIMER_PRESCALER_64,
    TIMER_PRESCALER_256,
    TIMER_PRESCALER_1024
} TIMER_ENUM_Prescalers;

// Timer/Counter Mode
typedef enum
{
    TIMER_MODE_FREE_RUNNING, // Timer Is Just Counting Until It Is Stopped.
    TIMER_MODE_EXECUTE_ONCE, // Timer Executes A Callback Once After Sometime, Then Stop.
    TIMER_MODE_REPEAT        // Timer Repeat A Callback Execution Until It Is Stopped.
} TIMER_ENUM_Modes;

// ---------------------------------------- Functions ---------------------------------------- //

void TIMER_Configure(TIMER_ENUM_Timers Copy_Timer, TIMER_ENUM_Modes Copy_Mode);

void TIMER_RegisterOnCompleteCallBack(TIMER_ENUM_Timers Copy_Timer, func_ptr Add_OnCompleteCallBack);

void TIMER_Start(TIMER_ENUM_Timers Copy_Timer, TIMER_ENUM_Prescalers Copy_Prescaler, u16 Copy_DesiredTimeMS);

void TIMER_Stop(TIMER_ENUM_Timers Copy_Timer);

u32 TIMER_Ticks(TIMER_ENUM_Timers Copy_Timer);

u8 TIMER_IsRunning(TIMER_ENUM_Timers Copy_Timer);

#endif
