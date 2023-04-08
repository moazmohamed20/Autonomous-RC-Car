#include <avr/io.h>
#include "WATCHDOG_int.h"
#include "../../LIB/bit_utils.h"

void WATCHDOG_Start(WATCHDOG_ENUM_TimeOuts Copy_TimeOut)
{
	// Watchdog Change Enable and WDE
	WDTCSR |= (1 << WDCE) | (1 << WDE);

	// Start Watchdog With TimeOut (Prescaler)
	WDTCSR = (1 << WDE) | (Copy_TimeOut & 7);
	ASSIGN_BIT(WDTCSR, WDP3, GET_BIT(Copy_TimeOut, 3));
}

void WATCHDOG_Reset()
{
	// Reset Watchdog Register
	asm("wdr");
}

void WATCHDOG_Stop()
{
	// Clear Watchdog System Reset Flag
	MCUSR &= ~(1 << WDRF);

	// Watchdog Change Enable and WDE
	WDTCSR |= (1 << WDCE) | (1 << WDE);

	// Stop The Watchdog Timer
	WDTCSR = 0x00;
}
