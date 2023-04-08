#include <avr/io.h>
#include "DIO_cfg.h"
#include "DIO_int.h"
#include "../../LIB/bit_utils.h"

void DIO_Init()
{
	// ReDefine As: OUTPUT = 1, INPUT =0
#undef DIO_OUTPUT_LOW
#undef DIO_OUTPUT_HIGH
#undef DIO_INPUT_FLOATING
#undef DIO_INPUT_PULLUP
#define DIO_OUTPUT_LOW 1
#define DIO_OUTPUT_HIGH 1
#define DIO_INPUT_FLOATING 0
#define DIO_INPUT_PULLUP 0

	// ------------------------------ Set DDR Registers Values ------------------------------ //
	DDRB = CONC_8bit(DIO_PORTB_PIN7_MODE, DIO_PORTB_PIN6_MODE, DIO_PORTB_PIN5_MODE, DIO_PORTB_PIN4_MODE, DIO_PORTB_PIN3_MODE, DIO_PORTB_PIN2_MODE, DIO_PORTB_PIN1_MODE, DIO_PORTB_PIN0_MODE);
	DDRC = CONC_8bit(DIO_PORTC_PIN7_MODE, DIO_PORTC_PIN6_MODE, DIO_PORTC_PIN5_MODE, DIO_PORTC_PIN4_MODE, DIO_PORTC_PIN3_MODE, DIO_PORTC_PIN2_MODE, DIO_PORTC_PIN1_MODE, DIO_PORTC_PIN0_MODE);
	DDRD = CONC_8bit(DIO_PORTD_PIN7_MODE, DIO_PORTD_PIN6_MODE, DIO_PORTD_PIN5_MODE, DIO_PORTD_PIN4_MODE, DIO_PORTD_PIN3_MODE, DIO_PORTD_PIN2_MODE, DIO_PORTD_PIN1_MODE, DIO_PORTD_PIN0_MODE);

	// ReDefine As: HIGH = 1, LOW =0
#undef DIO_OUTPUT_LOW
#undef DIO_OUTPUT_HIGH
#undef DIO_INPUT_FLOATING
#undef DIO_INPUT_PULLUP
#define DIO_OUTPUT_LOW 0
#define DIO_OUTPUT_HIGH 1
#define DIO_INPUT_FLOATING 0
#define DIO_INPUT_PULLUP 1

	// ------------------------------ Set PIN Registers Values ------------------------------ //
	PORTB = CONC_8bit(DIO_PORTB_PIN7_MODE, DIO_PORTB_PIN6_MODE, DIO_PORTB_PIN5_MODE, DIO_PORTB_PIN4_MODE, DIO_PORTB_PIN3_MODE, DIO_PORTB_PIN2_MODE, DIO_PORTB_PIN1_MODE, DIO_PORTB_PIN0_MODE);
	PORTC = CONC_8bit(DIO_PORTC_PIN7_MODE, DIO_PORTC_PIN6_MODE, DIO_PORTC_PIN5_MODE, DIO_PORTC_PIN4_MODE, DIO_PORTC_PIN3_MODE, DIO_PORTC_PIN2_MODE, DIO_PORTC_PIN1_MODE, DIO_PORTC_PIN0_MODE);
	PORTD = CONC_8bit(DIO_PORTD_PIN7_MODE, DIO_PORTD_PIN6_MODE, DIO_PORTD_PIN5_MODE, DIO_PORTD_PIN4_MODE, DIO_PORTD_PIN3_MODE, DIO_PORTD_PIN2_MODE, DIO_PORTD_PIN1_MODE, DIO_PORTD_PIN0_MODE);

	// Restore Initial Values
#undef DIO_OUTPUT_LOW
#undef DIO_OUTPUT_HIGH
#undef DIO_INPUT_FLOATING
#undef DIO_INPUT_PULLUP
#define DIO_OUTPUT_LOW 0
#define DIO_OUTPUT_HIGH 1
#define DIO_INPUT_FLOATING 2
#define DIO_INPUT_PULLUP 3
}

void DIO_SetPinValue(DIO_ENUM_Ports Copy_Port, DIO_ENUM_Pins Copy_Pin, DIO_ENUM_Values Copy_Value)
{
	switch (Copy_Port)
	{
	case DIO_PORTB:
		if (Copy_Value == DIO_HIGH)
			SET_BIT(PORTB, Copy_Pin);
		else
			CLR_BIT(PORTB, Copy_Pin);
		break;

	case DIO_PORTC:
		if (Copy_Value == DIO_HIGH)
			SET_BIT(PORTC, Copy_Pin);
		else
			CLR_BIT(PORTC, Copy_Pin);
		break;

	case DIO_PORTD:
		if (Copy_Value == DIO_HIGH)
			SET_BIT(PORTD, Copy_Pin);
		else
			CLR_BIT(PORTD, Copy_Pin);
		break;
	}
}

void DIO_SetPinDirection(DIO_ENUM_Ports Copy_Port, DIO_ENUM_Pins Copy_Pin, DIO_ENUM_Directions Copy_Direction)
{

	switch (Copy_Port)
	{
	case DIO_PORTB:
		if (Copy_Direction == DIO_OUTPUT)
			SET_BIT(DDRB, Copy_Pin);
		else
			CLR_BIT(DDRB, Copy_Pin);
		break;

	case DIO_PORTC:
		if (Copy_Direction == DIO_OUTPUT)
			SET_BIT(DDRC, Copy_Pin);
		else
			CLR_BIT(DDRC, Copy_Pin);
		break;

	case DIO_PORTD:
		if (Copy_Direction == DIO_OUTPUT)
			SET_BIT(DDRD, Copy_Pin);
		else
			CLR_BIT(DDRD, Copy_Pin);
		break;
	}
}

void DIO_TogglePinValue(DIO_ENUM_Ports Copy_Port, DIO_ENUM_Pins Copy_Pin)
{
	switch (Copy_Port)
	{
	case DIO_PORTB:
		TGL_BIT(PORTB, Copy_Pin);
		break;

	case DIO_PORTC:
		TGL_BIT(PORTC, Copy_Pin);
		break;

	case DIO_PORTD:
		TGL_BIT(PORTD, Copy_Pin);
		break;
	}
}

u8 DIO_GetPinValue(DIO_ENUM_Ports Copy_Port, DIO_ENUM_Pins Copy_Pin)
{
	u8 Local_PinValue;

	switch (Copy_Port)
	{
	case DIO_PORTB:
		Local_PinValue = GET_BIT(PINB, Copy_Pin);
		break;

	case DIO_PORTC:
		Local_PinValue = GET_BIT(PINC, Copy_Pin);
		break;

	case DIO_PORTD:
		Local_PinValue = GET_BIT(PIND, Copy_Pin);
		break;
	}

	return Local_PinValue;
}

void DIO_SetPortValue(DIO_ENUM_Ports Copy_Port, u8 Copy_PortValue)
{
	switch (Copy_Port)
	{
	case DIO_PORTB:
		PORTB = Copy_PortValue;
		break;

	case DIO_PORTC:
		PORTC = Copy_PortValue;
		break;

	case DIO_PORTD:
		PORTD = Copy_PortValue;
		break;
	}
}

void DIO_SetPortDirection(DIO_ENUM_Ports Copy_Port, DIO_ENUM_Directions Copy_Direction)
{
	switch (Copy_Port)
	{
	case DIO_PORTB:
		if (Copy_Direction == DIO_OUTPUT)
			SET_REG(DDRB);
		else
			CLR_REG(DDRB);
		break;

	case DIO_PORTC:
		if (Copy_Direction == DIO_OUTPUT)
			SET_REG(DDRC);
		else
			CLR_REG(DDRC);
		break;

	case DIO_PORTD:
		if (Copy_Direction == DIO_OUTPUT)
			SET_REG(DDRD);
		else
			CLR_REG(DDRD);
		break;
	}
}

void DIO_TogglePortValue(DIO_ENUM_Ports Copy_Port)
{
	switch (Copy_Port)
	{
	case DIO_PORTB:
		TGL_REG(PORTB);
		break;

	case DIO_PORTC:
		TGL_REG(PORTC);
		break;

	case DIO_PORTD:
		TGL_REG(PORTD);
		break;
	}
}

u8 DIO_GetPortValue(DIO_ENUM_Ports Copy_Port)
{
	u8 Local_PortValue;

	switch (Copy_Port)
	{
	case DIO_PORTB:
		Local_PortValue = PINB;
		break;

	case DIO_PORTC:
		Local_PortValue = PINC;
		break;

	case DIO_PORTD:
		Local_PortValue = PIND;
		break;
	}

	return Local_PortValue;
}
