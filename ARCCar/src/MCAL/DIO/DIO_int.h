#ifndef MCAL_DIO_DIO_INT_H_
#define MCAL_DIO_DIO_INT_H_

#include "../../LIB/std_types.h"

// ---------------------------------------- Enums ---------------------------------------- //

// Port Options
typedef enum
{
	DIO_PORTB,
	DIO_PORTC,
	DIO_PORTD
} DIO_ENUM_Ports;

// Pin Options
typedef enum
{
	DIO_PIN0,
	DIO_PIN1,
	DIO_PIN2,
	DIO_PIN3,
	DIO_PIN4,
	DIO_PIN5,
	DIO_PIN6,
	DIO_PIN7
} DIO_ENUM_Pins;

// Value Options
typedef enum
{
	DIO_LOW,
	DIO_HIGH
} DIO_ENUM_Values;

// Direction Options
typedef enum
{
	DIO_INPUT,
	DIO_OUTPUT
} DIO_ENUM_Directions;

// ---------------------------------------- Functions ---------------------------------------- //

void DIO_Init();

void DIO_SetPinValue(DIO_ENUM_Ports Copy_Port, DIO_ENUM_Pins Copy_Pin, DIO_ENUM_Values Copy_Value);

void DIO_SetPinDirection(DIO_ENUM_Ports Copy_Port, DIO_ENUM_Pins Copy_Pin, DIO_ENUM_Directions Copy_Direction);

void DIO_TogglePinValue(DIO_ENUM_Ports Copy_Port, DIO_ENUM_Pins Copy_Pin);

u8 DIO_GetPinValue(DIO_ENUM_Ports Copy_Port, DIO_ENUM_Pins Copy_Pin);

void DIO_SetPortValue(DIO_ENUM_Ports Copy_Port, u8 Copy_PortValue);

void DIO_SetPortDirection(DIO_ENUM_Ports Copy_Port, DIO_ENUM_Directions Copy_Direction);

void DIO_TogglePortValue(DIO_ENUM_Ports Copy_Port);

u8 DIO_GetPortValue(DIO_ENUM_Ports Copy_Port);

#endif
