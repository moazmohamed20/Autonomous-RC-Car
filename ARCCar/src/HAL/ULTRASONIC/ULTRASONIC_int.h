#ifndef HAL_ULTRASONIC_ULTRASONIC_INT_H_
#define HAL_ULTRASONIC_ULTRASONIC_INT_H_

#include "../../LIB/std_types.h"
#include "../../MCAL/TIMER/TIMER_int.h"
#include "../../MCAL/EXT_INT/EXT_INT_int.h"

// ---------------------------------------- Functions ---------------------------------------- //

void ULTRASONIC_Init(EXT_INT_ENUM_Interrupts Copy_Interrupt, TIMER_ENUM_Timers Copy_Timer);
f32 ULTRASONIC_GetDistanceCM();

#endif