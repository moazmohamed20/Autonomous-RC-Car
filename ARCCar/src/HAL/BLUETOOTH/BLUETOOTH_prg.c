#include "BLUETOOTH_int.h"

void BLUETOOTH_Init(u32 Copy_BaudRate, USART_ENUM_CharSize Copy_CharSize, USART_ENUM_Parity Copy_Parity, USART_ENUM_StopBits Copy_StopBits)
{
	USART_Init(Copy_BaudRate, Copy_CharSize, Copy_Parity, Copy_StopBits);
}

void BLUETOOTH_Init_2X(u32 Copy_BaudRate, USART_ENUM_CharSize Copy_CharSize, USART_ENUM_Parity Copy_Parity, USART_ENUM_StopBits Copy_StopBits)
{
	USART_Init_2X(Copy_BaudRate, Copy_CharSize, Copy_Parity, Copy_StopBits);
}

void BLUETOOTH_TransmitChar(char Copy_Char)
{
	USART_TransmitChar(Copy_Char);
}

void BLUETOOTH_TransmitString(char *Add_String)
{
	USART_TransmitString(Add_String);
}

void BLUETOOTH_TransmitNumber(f32 Copy_Number)
{
	USART_TransmitNumber(Copy_Number);
}

void BLUETOOTH_TransmitAsync(char *Add_TransmitData)
{
	USART_TransmitAsync(Add_TransmitData);
}

u8 BLUETOOTH_IsTransmitting()
{
	return USART_IsTransmitting();
}

u8 BLUETOOTH_Receive()
{
	return USART_Receive();
}

void BLUETOOTH_ReceiveAsync(u8 *Add_ReceivedData, u16 Copy_Size)
{
	USART_ReceiveAsync(Add_ReceivedData, Copy_Size);
}

u8 BLUETOOTH_IsReceiving()
{
	return USART_IsReceiving();
}