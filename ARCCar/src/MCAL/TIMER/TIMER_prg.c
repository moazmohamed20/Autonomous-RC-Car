#include <avr/interrupt.h>
#include "TIMER_int.h"

// Timers OnComplete CallBacks
static func_ptr TIMER_Timer0OnCompleteCallBack;
static func_ptr TIMER_Timer1OnCompleteCallBack;
static func_ptr TIMER_Timer2OnCompleteCallBack;

// Timers Modes
static TIMER_ENUM_Modes TIMER_Timer0Mode;
static TIMER_ENUM_Modes TIMER_Timer1Mode;
static TIMER_ENUM_Modes TIMER_Timer2Mode;

// Timers Initial OverFlows Counts
static u16 TIMER_Timer0InitialOVFCounts;
static u16 TIMER_Timer1InitialOVFCounts;
static u16 TIMER_Timer2InitialOVFCounts;

// Timers OverFlows Counters
static u16 TIMER_Timer0OVFCounter;
static u16 TIMER_Timer1OVFCounter;
static u16 TIMER_Timer2OVFCounter;

//  Timers Initial Values
static u8 TIMER_Timer0InitialValue;
static u16 TIMER_Timer1InitialValue;
static u8 TIMER_Timer2InitialValue;

// Prescaler Values
static const u16 TIMER_PRESCALER_VALUES[] = {0, 1, 8, 64, 256, 1024};

void TIMER_Configure(TIMER_ENUM_Timers Copy_Timer, TIMER_ENUM_Modes Copy_Mode)
{
    switch (Copy_Timer)
    {
    case TIMER_TIMER0:
        TIMER_Timer0Mode = Copy_Mode;
        TIMSK0 |= (1 << TOIE0);
        break;

    case TIMER_TIMER1:
        TIMER_Timer1Mode = Copy_Mode;
        TIMSK1 |= (1 << TOIE1);
        break;

    case TIMER_TIMER2:
        TIMER_Timer2Mode = Copy_Mode;
        TIMSK2 |= (1 << TOIE2);
        break;
    }
}

void TIMER_RegisterOnCompleteCallBack(TIMER_ENUM_Timers Copy_Timer, func_ptr Add_OnCompleteCallBack)
{
    switch (Copy_Timer)
    {
    case TIMER_TIMER0:
        TIMER_Timer0OnCompleteCallBack = Add_OnCompleteCallBack;
        break;

    case TIMER_TIMER1:
        TIMER_Timer1OnCompleteCallBack = Add_OnCompleteCallBack;
        break;

    case TIMER_TIMER2:
        TIMER_Timer2OnCompleteCallBack = Add_OnCompleteCallBack;
        break;
    }
}

void TIMER_Start(TIMER_ENUM_Timers Copy_Timer, TIMER_ENUM_Prescalers Copy_Prescaler, u16 Copy_DesiredTimeMS)
{
    // Stop Timer Timer If It Was Already Running
    TIMER_Stop(Copy_Timer);

    /*
     * To Convert From Sec -> nSec: x 1000,000,000
     * I Used Nano To Support Smallest Tick Time (Worst Case Down) 1/20,000,000 = 50 nS
     * I Used u32  To Support Highest Tick Time  (Worst Case UP) 1024/1,000,000 = 1,024,000 nS
     */
    u32 Local_u32TickTimeNS = TIMER_PRESCALER_VALUES[Copy_Prescaler] * 1e9 / F_CPU;

    switch (Copy_Timer)
    {
    case TIMER_TIMER0:
        if (TIMER_Timer0Mode == TIMER_MODE_FREE_RUNNING)
        {
            TIMER_Timer0InitialOVFCounts = TIMER_Timer0InitialValue = 0;
        }
        else
        {
            // Calculate The Number Of Overflows
            TIMER_Timer0InitialOVFCounts = (Copy_DesiredTimeMS * 1e6 / Local_u32TickTimeNS / 256);

            // Calculate The Remaining Ticks After Overflows
            TIMER_Timer0InitialValue = 256 - ((Copy_DesiredTimeMS * 1e6 / Local_u32TickTimeNS) - ((u32)TIMER_Timer0InitialOVFCounts * 256));
            // Increase The Overflows Number By 1 For The First Few Ticks
            if (TIMER_Timer0InitialValue > 0)
                TIMER_Timer0InitialOVFCounts++;
        }
        TIMER_Timer0OVFCounter = TIMER_Timer0InitialOVFCounts;

        // Fill The Timer Register With Initial Value
        TCNT0 = TIMER_Timer0InitialValue;

        // Start The Timer By Setting The Prescaler
        TCCR0B |= Copy_Prescaler;
        break;

    case TIMER_TIMER1:
        if (TIMER_Timer1Mode == TIMER_MODE_FREE_RUNNING)
        {
            TIMER_Timer1InitialOVFCounts = TIMER_Timer1InitialValue = 0;
        }
        else
        {
            // Calculate The Number Of Overflows
            TIMER_Timer1InitialOVFCounts = (Copy_DesiredTimeMS * 1e6 / Local_u32TickTimeNS / 65536);

            // Calculate The Remaining Ticks After Overflows
            TIMER_Timer1InitialValue = 65536 - ((Copy_DesiredTimeMS * 1e6 / Local_u32TickTimeNS) - ((u32)TIMER_Timer1InitialOVFCounts * 65536));
            // Increase The Overflows Number By 1 For The First Few Ticks
            if (TIMER_Timer1InitialValue > 0)
                TIMER_Timer1InitialOVFCounts++;
        }
        TIMER_Timer1OVFCounter = TIMER_Timer1InitialOVFCounts;

        // Fill The Timer Register With Initial Value
        TCNT1 = TIMER_Timer1InitialValue;

        // Start The Timer By Setting The Prescaler
        TCCR1B |= Copy_Prescaler;
        break;

    case TIMER_TIMER2:
        if (TIMER_Timer2Mode == TIMER_MODE_FREE_RUNNING)
        {
            TIMER_Timer2InitialOVFCounts = TIMER_Timer2InitialValue = 0;
        }
        else
        {
            // Calculate The Number Of Overflows
            TIMER_Timer2InitialOVFCounts = (Copy_DesiredTimeMS * 1e6 / Local_u32TickTimeNS / 256);

            // Calculate The Remaining Ticks After Overflows
            TIMER_Timer2InitialValue = 256 - ((Copy_DesiredTimeMS * 1e6 / Local_u32TickTimeNS) - ((u32)TIMER_Timer2InitialOVFCounts * 256));
            // Increase The Overflows Number By 1 For The First Few Ticks
            if (TIMER_Timer2InitialValue > 0)
                TIMER_Timer2InitialOVFCounts++;
        }
        TIMER_Timer2OVFCounter = TIMER_Timer2InitialOVFCounts;

        // Fill The Timer Register With Initial Value
        TCNT2 = TIMER_Timer2InitialValue;

        // Start The Timer By Setting The Prescaler
        TCCR2B |= (Copy_Prescaler + (Copy_Prescaler / TIMER_PRESCALER_64) + (Copy_Prescaler / TIMER_PRESCALER_256) + (Copy_Prescaler / TIMER_PRESCALER_1024));
        break;
    }
}

void TIMER_Stop(TIMER_ENUM_Timers Copy_Timer)
{
    switch (Copy_Timer)
    {
    case TIMER_TIMER0:
        TCCR0B &= 0xF8;
        break;

    case TIMER_TIMER1:
        TCCR1B &= 0xF8;
        break;

    case TIMER_TIMER2:
        TCCR2B &= 0xF8;
        break;
    }
}

u32 TIMER_Ticks(TIMER_ENUM_Timers Copy_Timer)
{
    u32 Local_TimerTicks;

    switch (Copy_Timer)
    {
    case TIMER_TIMER0:
        Local_TimerTicks = TCNT0 + TIMER_Timer0OVFCounter * 256;
        break;

    case TIMER_TIMER1:
        Local_TimerTicks = TCNT1 + TIMER_Timer1OVFCounter * 65536;
        break;

    case TIMER_TIMER2:
        Local_TimerTicks = TCNT2 + TIMER_Timer2OVFCounter * 256;
        break;
    }

    return Local_TimerTicks;
}

u8 TIMER_IsRunning(TIMER_ENUM_Timers Copy_Timer)
{
    u8 Local_IsRunning = FALSE;

    switch (Copy_Timer)
    {
    case TIMER_TIMER0:
        Local_IsRunning = (TCCR0B & 7);
        break;

    case TIMER_TIMER1:
        Local_IsRunning = (TCCR1B & 7);
        break;

    case TIMER_TIMER2:
        Local_IsRunning = (TCCR2B & 7);
        break;
    }

    return Local_IsRunning;
}

// --------------------------------------------------------- ISR --------------------------------------------------------- //

// Timer 0 Overflow Interrupt Request
ISR(TIMER0_OVF_vect)
{
    if (TIMER_Timer0Mode == TIMER_MODE_FREE_RUNNING)
        TIMER_Timer0OVFCounter++;

    else if (--TIMER_Timer0OVFCounter == 0)
    {
        if (TIMER_Timer0Mode == TIMER_MODE_EXECUTE_ONCE)
            TCCR0B &= 0xF8; // Stop The Timer

        else
        {
            // Reset Overflow Counter
            TIMER_Timer0OVFCounter = TIMER_Timer0InitialOVFCounts;
            // ReFill The Timer Register With Initial Value
            TCNT0 = TIMER_Timer0InitialValue;
        }

        // Execute The Callback
        if (TIMER_Timer0OnCompleteCallBack != NULL)
            TIMER_Timer0OnCompleteCallBack();
    }
}

// Timer 1 Overflow Interrupt Request
ISR(TIMER1_OVF_vect)
{
    if (TIMER_Timer1Mode == TIMER_MODE_FREE_RUNNING)
        TIMER_Timer1OVFCounter++;

    else if (--TIMER_Timer1OVFCounter == 0)
    {
        if (TIMER_Timer1Mode == TIMER_MODE_EXECUTE_ONCE)
            TCCR1B &= 0xF8; // Stop The Timer

        else
        {
            // Reset Overflow Counter
            TIMER_Timer1OVFCounter = TIMER_Timer1InitialOVFCounts;
            // ReFill The Timer Register With Initial Value
            TCNT1 = TIMER_Timer1InitialValue;
        }

        // Execute The Callback
        if (TIMER_Timer1OnCompleteCallBack != NULL)
            TIMER_Timer1OnCompleteCallBack();
    }
}

// Timer 2 Overflow Interrupt Request
ISR(TIMER2_OVF_vect)
{
    if (TIMER_Timer2Mode == TIMER_MODE_FREE_RUNNING)
        TIMER_Timer2OVFCounter++;

    else if (--TIMER_Timer2OVFCounter == 0)
    {
        if (TIMER_Timer2Mode == TIMER_MODE_EXECUTE_ONCE)
            TCCR0B &= 0xF8; // Stop The Timer

        else
        {
            // Reset Overflow Counter
            TIMER_Timer2OVFCounter = TIMER_Timer2InitialOVFCounts;
            // ReFill The Timer Register With Initial Value
            TCNT0 = TIMER_Timer0InitialValue;
        }

        // Execute The Callback
        if (TIMER_Timer2OnCompleteCallBack != NULL)
            TIMER_Timer2OnCompleteCallBack();
    }
}