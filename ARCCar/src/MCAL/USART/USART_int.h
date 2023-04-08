#ifndef MCAL_USART_USART_INT_H_
#define MCAL_USART_USART_INT_H_

#include "../../LIB/std_types.h"

// ---------------------------------------- Enums ---------------------------------------- //

typedef enum
{
	USART_CHAR_SIZE_5_BIT,
	USART_CHAR_SIZE_6_BIT,
	USART_CHAR_SIZE_7_BIT,
	USART_CHAR_SIZE_8_BIT
} USART_ENUM_CharSize;

typedef enum
{
	USART_PARITY_NONE,
	USART_PARITY_EVEN,
	USART_PARITY_ODD
} USART_ENUM_Parity;

typedef enum
{
	USART_STOP_BITS_ONE,
	USART_STOP_BITS_TWO
} USART_ENUM_StopBits;

typedef enum
{
	USART_STOP_DISABLE,
	USART_U2X_ENABLE
} USART_ENUM_U2X;

// ---------------------------------------- Functions ---------------------------------------- //

void USART_Init(u32 Copy_BaudRate, USART_ENUM_CharSize Copy_CharSize, USART_ENUM_Parity Copy_Parity, USART_ENUM_StopBits Copy_StopBits);

void USART_Init_2X(u32 Copy_BaudRate, USART_ENUM_CharSize Copy_CharSize, USART_ENUM_Parity Copy_Parity, USART_ENUM_StopBits Copy_StopBits);

void USART_TransmitChar(char Copy_Char);

void USART_TransmitString(char *Add_String);

void USART_TransmitNumber(f32 Copy_Number);

void USART_TransmitAsync(char *Add_TransmitData);

u8 USART_IsTransmitting();

u8 USART_Receive();

void USART_ReceiveAsync(u8 *Add_ReceivedData, u16 Copy_Size);

u8 USART_IsReceiving();

#endif
