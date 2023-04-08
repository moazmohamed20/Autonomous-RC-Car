#ifndef MCAL_PWM_PWM_INT_H_
#define MCAL_PWM_PWM_INT_H_

#include "../../LIB/std_types.h"

// ---------------------------------------- Enums ---------------------------------------- //

typedef enum
{
	PWM_PWM0,
	PWM_PWM1,
	PWM_PWM2
} PWM_ENUM_PWMs;

typedef enum
{
	PWM_PRESCALER_1 = 1,
	PWM_PRESCALER_8,
	PWM_PRESCALER_64,
	PWM_PRESCALER_256,
	PWM_PRESCALER_1024
} PWM_ENUM_Prescalers;

typedef enum
{
	/*
	 * Set PWM Wave Generation Mode:
	 * 		Fast PWM:			/|/|/|/| - Ascending UP, Immediate Down
	 * 		Phase Correct PWM:	/\/\/\/\ - Ascending UP, Descending Down
	 */
	PWM_WGM_FAST_PWM0 = 3,
	PWM_WGM_FAST_PWM1 = 14,
	PWM_WGM_FAST_PWM2 = 3,
	PWM_WGM_PHASE_CORRECT_PWM0 = 1,
	PWM_WGM_PHASE_CORRECT_PWM1 = 8,
	PWM_WGM_PHASE_CORRECT_PWM2 = 1
} PWM_ENUM_WaveGenerationModes;

typedef enum
{
	PWM_PIN_OC0A,
	PWM_PIN_OC0B,
	PWM_PIN_OC1A,
	PWM_PIN_OC1B,
	PWM_PIN_OC2A,
	PWM_PIN_OC2B
} PWM_ENUM_Pins;

typedef enum
{
	PWM_PIN_MODE_DISCONNECTED,
	PWM_PIN_MODE_NON_INVERTING = 2, // Clear On Compare Match, Set At BOTTOM: ‾‾‾|___
	PWM_PIN_MODE_INVERTING			// Set On Compare Match, Clear At BOTTOM: ___|‾‾‾
} PWM_ENUM_PinModes;

// ---------------------------------------- Functions ---------------------------------------- //

void PWM_Configure(PWM_ENUM_PWMs Copy_PWM, PWM_ENUM_Prescalers Copy_Prescaler, PWM_ENUM_WaveGenerationModes Copy_WaveGenerationMode, u16 Copy_TopValue);

void PWM_ConfigurePin(PWM_ENUM_Pins Copy_Pin, PWM_ENUM_PinModes Copy_PinMode, u16 Copy_DutyValue);

void PWM_StartPWM(PWM_ENUM_PWMs Copy_PWM);

void PWM_StopPWM(PWM_ENUM_PWMs Copy_PWM);

#endif