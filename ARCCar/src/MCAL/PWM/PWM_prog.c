#include <avr/io.h>
#include "PWM_int.h"
#include "../../LIB/bit_utils.h"

static PWM_ENUM_Prescalers PWM_Timer0Prescaler;
static PWM_ENUM_Prescalers PWM_Timer1Prescaler;
static PWM_ENUM_Prescalers PWM_Timer2Prescaler;

void PWM_Configure(PWM_ENUM_PWMs Copy_PWM, PWM_ENUM_Prescalers Copy_Prescaler, PWM_ENUM_WaveGenerationModes Copy_WaveGenerationMode, u16 Copy_TopValue)
{
	switch (Copy_PWM)
	{
	case PWM_PWM0:
		// Remember Prescaler To Be Used When PWM_Start() Called
		PWM_Timer0Prescaler = Copy_Prescaler;

		// Set Timer Wave Generation Mode
		ASSIGN_BIT(TCCR0A, WGM00, GET_BIT(Copy_WaveGenerationMode, 0));
		ASSIGN_BIT(TCCR0A, WGM01, GET_BIT(Copy_WaveGenerationMode, 1));

		// Timer TOP Value Is: 255
		break;

	case PWM_PWM1:
		// Remember Prescaler To Be Used When PWM_Start() Called
		PWM_Timer1Prescaler = Copy_Prescaler;

		// Set Timer Wave Generation Mode
		ASSIGN_BIT(TCCR1A, WGM10, GET_BIT(Copy_WaveGenerationMode, 0));
		ASSIGN_BIT(TCCR1A, WGM11, GET_BIT(Copy_WaveGenerationMode, 1));
		ASSIGN_BIT(TCCR1B, WGM12, GET_BIT(Copy_WaveGenerationMode, 2));
		ASSIGN_BIT(TCCR1B, WGM13, GET_BIT(Copy_WaveGenerationMode, 3));

		// Set Timer TOP Value
		ICR1 = Copy_TopValue;
		break;

	case PWM_PWM2:
		// Remember Prescaler To Be Used When PWM_Start() Called
		PWM_Timer2Prescaler = (Copy_Prescaler + (Copy_Prescaler / PWM_PRESCALER_64) + (Copy_Prescaler / PWM_PRESCALER_256) + (Copy_Prescaler / PWM_PRESCALER_1024));

		// Set Timer Wave Generation Mode
		ASSIGN_BIT(TCCR2A, WGM20, GET_BIT(Copy_WaveGenerationMode, 0));
		ASSIGN_BIT(TCCR2A, WGM21, GET_BIT(Copy_WaveGenerationMode, 1));

		// Timer TOP Value Is: 255
		break;
	}
}

void PWM_ConfigurePin(PWM_ENUM_Pins Copy_Pin, PWM_ENUM_PinModes Copy_PinMode, u16 Copy_DutyValue)
{
	switch (Copy_Pin)
	{
	case PWM_PIN_OC0A:
		// Set OC0A Compare Value (Duty Value)
		OCR0A = Copy_DutyValue;

		// According To Datasheet: The Minimum Value Allowed Is 3
		if (Copy_DutyValue < 3)
			Copy_PinMode = PWM_PIN_MODE_DISCONNECTED;

		// Set OC0A Pin Mode
		TCCR0A &= ~(3 << COM0A0);
		TCCR0A |= (Copy_PinMode << COM0A0);
		break;

	case PWM_PIN_OC0B:
		// Set OC0B Compare Value (Duty Value)
		OCR0B = Copy_DutyValue;

		// According To Datasheet: The Minimum Value Allowed Is 3
		if (Copy_DutyValue < 3)
			Copy_PinMode = PWM_PIN_MODE_DISCONNECTED;

		// Set OC0B Pin Mode
		TCCR0A &= ~(3 << COM0B0);
		TCCR0A |= (Copy_PinMode << COM0B0);
		break;

	case PWM_PIN_OC1A:
		// Set OC1A Compare Value (Duty Value)
		OCR1A = Copy_DutyValue;

		if (Copy_DutyValue < 3)
			Copy_PinMode = PWM_PIN_MODE_DISCONNECTED;

		// According To Datasheet: The Minimum Value Allowed Is 3
		// Set OC1A Pin Mode
		TCCR1A &= ~(3 << COM1A0);
		TCCR1A |= (Copy_PinMode << COM1A0);
		break;

	case PWM_PIN_OC1B:
		// Set OC1B Compare Value (Duty Value)
		OCR1B = Copy_DutyValue;

		// According To Datasheet: The Minimum Value Allowed Is 3
		if (Copy_DutyValue < 3)
			Copy_PinMode = PWM_PIN_MODE_DISCONNECTED;

		// Set OC1B Pin Mode
		TCCR1A &= ~(3 << COM1B0);
		TCCR1A |= (Copy_PinMode << COM1B0);
		break;

	case PWM_PIN_OC2A:
		// Set OC2A Compare Value (Duty Value)
		OCR2A = Copy_DutyValue;

		// According To Datasheet: The Minimum Value Allowed Is  3
		if (Copy_DutyValue < 3)
			Copy_PinMode = PWM_PIN_MODE_DISCONNECTED;

		// Set OC2A Pin Mode
		TCCR2A &= ~(3 << COM2A0);
		TCCR2A |= (Copy_PinMode << COM2A0);
		break;

	case PWM_PIN_OC2B:
		// Set OC2B Compare Value (Duty Value)
		OCR2B = Copy_DutyValue;

		// According To Datasheet: The Minimum Value Allowed Is  3
		if (Copy_DutyValue < 3)
			Copy_PinMode = PWM_PIN_MODE_DISCONNECTED;

		// Set OC2B Pin Mode
		TCCR2A &= ~(3 << COM2B0);
		TCCR2A |= (Copy_PinMode << COM2B0);
		break;
	}
}

void PWM_StartPWM(PWM_ENUM_PWMs Copy_PWM)
{
	switch (Copy_PWM)
	{
	case PWM_PWM0:
		TCCR0B &= 0xF8;
		TCCR0B |= PWM_Timer0Prescaler;
		break;

	case PWM_PWM1:
		TCCR1B &= 0xF8;
		TCCR1B |= PWM_Timer1Prescaler;
		break;

	case PWM_PWM2:
		TCCR2B &= 0xF8;
		TCCR2B |= PWM_Timer2Prescaler;
		break;
	}
}

void PWM_StopPWM(PWM_ENUM_PWMs Copy_PWM)
{
	switch (Copy_PWM)
	{
	case PWM_PWM0:
		TCCR0B &= 0xF8;
		break;

	case PWM_PWM1:
		TCCR1B &= 0xF8;
		break;

	case PWM_PWM2:
		TCCR2B &= 0xF8;
		break;
	}
}
