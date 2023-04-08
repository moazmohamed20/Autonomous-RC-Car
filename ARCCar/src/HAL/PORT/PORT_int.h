#ifndef HAL_PORT_PORT_INT_H_
#define HAL_PORT_PORT_INT_H_

#include "../../MCAL/DIO/DIO_int.h"

// ---------------------------------------- Functions ---------------------------------------- //

void PORT_Init();

void PORT_SetPinValue(DIO_ENUM_Ports Copy_Port, DIO_ENUM_Pins Copy_Pin, DIO_ENUM_Values Copy_Value);

void PORT_SetPinDirection(DIO_ENUM_Ports Copy_Port, DIO_ENUM_Pins Copy_Pin, DIO_ENUM_Directions Copy_Direction);

void PORT_TogglePinValue(DIO_ENUM_Ports Copy_Port, DIO_ENUM_Pins Copy_Pin);

u8 PORT_GetPinValue(DIO_ENUM_Ports Copy_Port, DIO_ENUM_Pins Copy_Pin);

void PORT_SetPortValue(DIO_ENUM_Ports Copy_Port, u8 Copy_PortValue);

void PORT_SetPortDirection(DIO_ENUM_Ports Copy_Port, DIO_ENUM_Directions Copy_Direction);

void PORT_TogglePortValue(DIO_ENUM_Ports Copy_Port);

u8 PORT_GetPortValue(DIO_ENUM_Ports Copy_Port);

#endif
