#include <util/delay.h>
#include "ULTRASONIC_cfg.h"
#include "ULTRASONIC_int.h"
#include "../../MCAL/DIO/DIO_int.h"

/*
 ****************
 * How It Works *
 ****************
 * Trigger Pin: _____|‾|________________________________
 *   When It Goes HIGH For 10us+, The Sensor Fires 8 Ultrasonic Pulses
 *
 * Echo Pin:	_________|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|___
 * 	 Goes High When The Ultrasonic Pulses Are Transmitted,
 * 	 And Remains High Until The Sensor Receives The Reflected Echo
 */

static TIMER_ENUM_Timers ULTRASONIC_Timer;
static u32 ULTRASONIC_EchoPulseTime;

static void ULTRASONIC_Trigger();
static void ULTRASONIC_EchoChanged();

void ULTRASONIC_Init(EXT_INT_ENUM_Interrupts Copy_Interrupt, TIMER_ENUM_Timers Copy_Timer)
{
	// Enable External Interrupt: To Detect Rising & Falling Edges Of Echo Pin
	EXT_INT_Enable(Copy_Interrupt, EXT_INT_TRIGGER_ANY_CHANGE, ULTRASONIC_EchoChanged);

	// Configure Timer In Free Running Mode: To Calculate The Width Of The Echo Pulse
	TIMER_Configure(Copy_Timer, TIMER_MODE_FREE_RUNNING);

	// Remember The Timer To Be Used In Interrupt ISR
	ULTRASONIC_Timer = Copy_Timer;
}

f32 ULTRASONIC_GetDistanceCM()
{
	// Fire The Trigger Pulse
	ULTRASONIC_Trigger();

	// Wait Until Echo Goes HIGH, Or Timeout Is Reached
	u8 timeout = 0xFF;
	while (DIO_GetPinValue(ULTRASONIC_ECHO_PORT, ULTRASONIC_ECHO_PIN) == 0 && timeout--)
		;

	// Wait Until Echo Goes LOW, Or Timeout Is Reached
	timeout = 0xFF;
	while (DIO_GetPinValue(ULTRASONIC_ECHO_PORT, ULTRASONIC_ECHO_PIN) == 1 && timeout--)
		;

	// Wait 10 ms To Separate Between This Echo & The Next Trigger
	_delay_ms(10);

	/*
	 * distance (Go + Back)	= time * velocity
	 * distance (Go Only)	= time * velocity * 0.5
	 *
	 * time		= ULTRASONIC_EchoPulseTime
	 * velocity = Speed Of Sound In Air	(343 m/s = 0.0343 cm/us)
	 *
	 * distance = ULTRASONIC_EchoPulseTime * 0.0343 * 0.5
	 * 			= ULTRASONIC_EchoPulseTime / 58.0
	 */
	return ULTRASONIC_EchoPulseTime / 58.0;
}

static void ULTRASONIC_Trigger()
{
	DIO_SetPinValue(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, DIO_HIGH);
	_delay_us(10);
	DIO_SetPinValue(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, DIO_LOW);
}

static void ULTRASONIC_EchoChanged()
{
	// On Echo Rising Edge (Init & Start Timer)
	if (DIO_GetPinValue(ULTRASONIC_ECHO_PORT, ULTRASONIC_ECHO_PIN) == 1)
	{
		ULTRASONIC_EchoPulseTime = 0;						 // Clear Old Reading
		TIMER_Start(ULTRASONIC_Timer, TIMER_PRESCALER_1, 0); // Start Timer, With  Prescaler = 1 (1MHz/1 = 1MHz => 1 Tick = 1 us)
	}
	// On Echo Falling Edge (Stop Timer & Read)
	else
	{
		TIMER_Stop(ULTRASONIC_Timer);							  // Stop Timer
		ULTRASONIC_EchoPulseTime = TIMER_Ticks(ULTRASONIC_Timer); // Read The Number Of Ticks That Timer Made (1 Tick = 1 us)
	}
}
