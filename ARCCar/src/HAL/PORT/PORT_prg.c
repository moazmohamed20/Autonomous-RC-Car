#include "PORT_int.h"

void PORT_Init()
{
	DIO_Init();
}

void PORT_SetPinValue(DIO_ENUM_Ports Copy_Port, DIO_ENUM_Pins Copy_Pin, DIO_ENUM_Values Copy_Value)
{
	DIO_SetPinValue(Copy_Port, Copy_Pin, Copy_Value);
}

void PORT_SetPinDirection(DIO_ENUM_Ports Copy_Port, DIO_ENUM_Pins Copy_Pin, DIO_ENUM_Directions Copy_Direction)
{
	DIO_SetPinDirection(Copy_Port, Copy_Pin, Copy_Direction);
}

void PORT_TogglePinValue(DIO_ENUM_Ports Copy_Port, DIO_ENUM_Pins Copy_Pin)
{
	DIO_TogglePinValue(Copy_Port, Copy_Pin);
}

u8 PORT_GetPinValue(DIO_ENUM_Ports Copy_Port, DIO_ENUM_Pins Copy_Pin)
{
	return DIO_GetPinValue(Copy_Port, Copy_Pin);
}

void PORT_SetPortValue(DIO_ENUM_Ports Copy_Port, u8 Copy_PortValue)
{
	DIO_SetPortValue(Copy_Port, Copy_PortValue);
}
void PORT_SetPortDirection(DIO_ENUM_Ports Copy_Port, DIO_ENUM_Directions Copy_Direction)
{
	DIO_SetPortDirection(Copy_Port, Copy_Direction);
}

void PORT_TogglePortValue(DIO_ENUM_Ports Copy_Port)
{
	DIO_TogglePortValue(Copy_Port);
}

u8 PORT_GetPortValue(DIO_ENUM_Ports Copy_Port)
{
	return DIO_GetPortValue(Copy_Port);
}
