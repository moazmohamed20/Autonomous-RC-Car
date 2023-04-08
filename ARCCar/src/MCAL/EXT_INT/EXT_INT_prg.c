#include <avr/interrupt.h>
#include "EXT_INT_int.h"
#include "../../LIB/Bit_Utils.h"

static func_ptr EXT_INT_INT0_CALLBACK;
static func_ptr EXT_INT_INT1_CALLBACK;

void EXT_INT_Enable(EXT_INT_ENUM_Interrupts Copy_Interrupt, EXT_INT_ENUM_Triggers Copy_Trigger, func_ptr Add_ISRCallback)
{
	switch (Copy_Interrupt)
	{
	case EXT_INT_INT0:
		// INT0 Trigger
		switch (Copy_Trigger)
		{
		case EXT_INT_TRIGGER_LOW_LEVEL:
			CLR_BIT(EICRA, ISC00);
			CLR_BIT(EICRA, ISC01);
			break;
		case EXT_INT_TRIGGER_ANY_CHANGE:
			SET_BIT(EICRA, ISC00);
			CLR_BIT(EICRA, ISC01);
			break;
		case EXT_INT_TRIGGER_FALLING_EDGE:
			CLR_BIT(EICRA, ISC00);
			SET_BIT(EICRA, ISC01);
			break;
		case EXT_INT_TRIGGER_RISING_EDGE:
			SET_BIT(EICRA, ISC00);
			SET_BIT(EICRA, ISC01);
			break;
		}
		// Enable INT0
		SET_BIT(EIMSK, INT0);
		// INT0  ISR CallBack
		EXT_INT_INT0_CALLBACK = Add_ISRCallback;
		break;

	case EXT_INT_INT1:
		// INT1 Trigger
		switch (Copy_Trigger)
		{
		case EXT_INT_TRIGGER_LOW_LEVEL:
			CLR_BIT(EICRA, ISC10);
			CLR_BIT(EICRA, ISC11);
			break;
		case EXT_INT_TRIGGER_ANY_CHANGE:
			SET_BIT(EICRA, ISC10);
			CLR_BIT(EICRA, ISC11);
			break;
		case EXT_INT_TRIGGER_FALLING_EDGE:
			CLR_BIT(EICRA, ISC10);
			SET_BIT(EICRA, ISC11);
			break;
		case EXT_INT_TRIGGER_RISING_EDGE:
			SET_BIT(EICRA, ISC10);
			SET_BIT(EICRA, ISC11);
			break;
		}
		// Enable INT1
		SET_BIT(EIMSK, INT1);
		// INT1  ISR CallBack
		EXT_INT_INT1_CALLBACK = Add_ISRCallback;
		break;
	}
}

void EXT_INT_Disable(EXT_INT_ENUM_Interrupts Copy_Interrupt)
{
	switch (Copy_Interrupt)
	{
	case EXT_INT_INT0:
		CLR_BIT(EIMSK, INT0);
		break;

	case EXT_INT_INT1:
		CLR_BIT(EIMSK, INT1);
		break;
	}
}

// --------------------------------------------------------- ISRs --------------------------------------------------------- //

// External Interrupt Request 0
ISR(INT0_vect)
{
	if (EXT_INT_INT0_CALLBACK != NULL)
		EXT_INT_INT0_CALLBACK();
}

// External Interrupt Request 1
ISR(INT1_vect)
{
	if (EXT_INT_INT1_CALLBACK != NULL)
		EXT_INT_INT1_CALLBACK();
}
