#ifndef MCAL_BLUETOOTH_BLUETOOTH_INT_H_
#define MCAL_BLUETOOTH_BLUETOOTH_INT_H_

#include "../../LIB/std_types.h"
#include "../../MCAL/USART/USART_int.h"

// ---------------------------------------- Functions ---------------------------------------- //

void BLUETOOTH_Init(u32 Copy_BaudRate, USART_ENUM_CharSize Copy_CharSize, USART_ENUM_Parity Copy_Parity, USART_ENUM_StopBits Copy_StopBits);

void BLUETOOTH_Init_2X(u32 Copy_BaudRate, USART_ENUM_CharSize Copy_CharSize, USART_ENUM_Parity Copy_Parity, USART_ENUM_StopBits Copy_StopBits);

void BLUETOOTH_EnableU2X();

void BLUETOOTH_DisableU2X();

void BLUETOOTH_TransmitChar(char Copy_Char);

void BLUETOOTH_TransmitString(char *Add_String);

void BLUETOOTH_TransmitNumber(f32 Copy_Number);

void BLUETOOTH_TransmitAsync(char *Add_TransmitData);

u8 BLUETOOTH_IsTransmitting();

u8 BLUETOOTH_Receive();

void BLUETOOTH_ReceiveAsync(u8 *Add_ReceivedData, u16 Copy_Size);

u8 BLUETOOTH_IsReceiving();

#endif
