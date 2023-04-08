#ifndef MCAL_WATCHDOG_WATCHDOG_INT_H_
#define MCAL_WATCHDOG_WATCHDOG_INT_H_

// ---------------------------------------- Enums ---------------------------------------- //

// WATCHDOG TimeOuts
typedef enum
{
	WATCHDOG_TIMEOUT_16_ms,
	WATCHDOG_TIMEOUT_32_ms,
	WATCHDOG_TIMEOUT_64_ms,
	WATCHDOG_TIMEOUT_125_ms,
	WATCHDOG_TIMEOUT_250_ms,
	WATCHDOG_TIMEOUT_500_ms,
	WATCHDOG_TIMEOUT_1000_ms,
	WATCHDOG_TIMEOUT_2000_ms,
	WATCHDOG_TIMEOUT_4000_ms,
	WATCHDOG_TIMEOUT_8000_ms
} WATCHDOG_ENUM_TimeOuts;

// ---------------------------------------- Functions ---------------------------------------- //

void WATCHDOG_Start(WATCHDOG_ENUM_TimeOuts Copy_TimeOut);

void WATCHDOG_Reset();

void WATCHDOG_Stop();

#endif
