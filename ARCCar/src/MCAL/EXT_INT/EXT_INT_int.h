#ifndef MCAL_EXT_INT_EXT_INT_INT_H_
#define MCAL_EXT_INT_EXT_INT_INT_H_

#include "../../LIB/std_types.h"

// ---------------------------------------- Enums ---------------------------------------- //

// Interrupts
typedef enum
{
	EXT_INT_INT0,
	EXT_INT_INT1
} EXT_INT_ENUM_Interrupts;

// Interrupt Triggers
typedef enum
{
	EXT_INT_TRIGGER_LOW_LEVEL,
	EXT_INT_TRIGGER_ANY_CHANGE,
	EXT_INT_TRIGGER_FALLING_EDGE,
	EXT_INT_TRIGGER_RISING_EDGE
} EXT_INT_ENUM_Triggers;

// ---------------------------------------- Functions ---------------------------------------- //

void EXT_INT_Enable(EXT_INT_ENUM_Interrupts Copy_Interrupt, EXT_INT_ENUM_Triggers Copy_Trigger, func_ptr Add_ISRCallback);

void EXT_INT_Disable(EXT_INT_ENUM_Interrupts Copy_Interrupt);

#endif
