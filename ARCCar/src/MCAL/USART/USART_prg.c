#include <avr/interrupt.h>
#include "USART_int.h"

char *USART_TransmitData;
u8 *USART_ReceivedData;
u8 USART_ReceivedDataSize;

static void TransmitDigit(u16 Copy_Digit);

void USART_Init(u32 Copy_BaudRate, USART_ENUM_CharSize Copy_CharSize, USART_ENUM_Parity Copy_Parity, USART_ENUM_StopBits Copy_StopBits)
{
	// Calculate UBRR
	u16 Local_UBRR = F_CPU / 16 / Copy_BaudRate - 1;
	UBRR0 = Local_UBRR;

	// Set Char Size
	UCSR0C = (Copy_CharSize << UCSZ00); // Set:   UCSZ1:0

	// Set Parity Mode
	UCSR0C |= (Copy_Parity << UPM00); // Set:   UPM1:0

	// Set Stop Bits
	UCSR0C |= (Copy_StopBits << USBS0);

	// Enable Receiver & Transmitter
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
}

void USART_Init_2X(u32 Copy_BaudRate, USART_ENUM_CharSize Copy_CharSize, USART_ENUM_Parity Copy_Parity, USART_ENUM_StopBits Copy_StopBits)
{
	// Enable Double Speed
	UCSR0A |= (1 << U2X0);

	// Calculate UBRR
	u16 Local_UBRR = F_CPU / 8 / Copy_BaudRate - 1;
	UBRR0 = Local_UBRR;

	// Set Char Size
	UCSR0C = (Copy_CharSize << UCSZ00); // Set:   UCSZ1:0

	// Set Parity Mode
	UCSR0C |= (Copy_Parity << UPM00); // Set:   UPM1:0

	// Set Stop Bits
	UCSR0C |= (Copy_StopBits << USBS0);

	// Enable Receiver & Transmitter
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
}

void USART_TransmitChar(char Copy_Char)
{
	// Wait For Data Register To Be Empty (Ready For New Data To Be Put Into)
	while ((UCSR0A & (1 << UDRE0)) == 0)
		;

	// Copy Data Into Buffer
	UDR0 = Copy_Char;
}

void USART_TransmitString(char *Add_String)
{
	while (*Add_String != '\0')
		USART_TransmitChar(*(Add_String++));
}

void USART_TransmitNumber(f32 Copy_Number)
{
	// Convert: Negative Number -> Positive Number
	if (Copy_Number < 0)
	{
		USART_TransmitChar('-');
		Copy_Number = -Copy_Number;
	}

	// Divide Number Into Two Parts: Integral_Part.Fractional_Part
	u16 Local_IntPart = (u16)Copy_Number;
	u16 Local_FracPart = (Copy_Number - Local_IntPart) * 10000;

	// Print Integral Part
	TransmitDigit(Local_IntPart);

	// Print Fractional Part
	if (Local_FracPart > 0)
	{
		USART_TransmitChar('.');
		TransmitDigit(Local_FracPart);
	}
}

static void TransmitDigit(u16 Copy_Digit)
{
	if (Copy_Digit > 9)
		USART_TransmitNumber(Copy_Digit / 10);
	USART_TransmitChar((Copy_Digit % 10) + 0x30);
}

void USART_TransmitAsync(char *Add_TransmitData)
{
	// Remember The Address Of Data To Be Transmitted (For Interrupt To Use)
	USART_TransmitData = Add_TransmitData;

	// Enable Transmit Complete & Data Register Empty Interrupts
	UCSR0B |= ((1 << TXCIE0) | (1 << UDRIE0));
}

u8 USART_IsTransmitting()
{
	return !((UCSR0A >> TXC0) & 1);
}

u8 USART_Receive()
{
	// Wait For Data To Be Received
	while ((UCSR0A & (1 << RXC0)) == 0)
		;

	// Return Data From Buffer
	return UDR0;
}

void USART_ReceiveAsync(u8 *Add_ReceivedData, u16 Copy_Size)
{
	// Remember The Address Of Where Received Data To Be Stored (For Interrupt To Use)
	USART_ReceivedData = Add_ReceivedData;
	USART_ReceivedDataSize = Copy_Size;

	// Enable Receive Complete Interrupts
	UCSR0B |= (1 << RXCIE0);
}

u8 USART_IsReceiving()
{
	return ((UCSR0B >> RXCIE0) & 1);
}

// --------------------------------------------------------- ISR --------------------------------------------------------- //

// Data Register Empty Interrupt Request
ISR(USART_UDRE_vect)
{
	if (*USART_TransmitData != '\0')
		UDR0 = *USART_TransmitData++;
}

// Transmit Complete Interrupt Request
ISR(USART_TX_vect)
{
	// ToDo:
	// Disable Transmit Complete & Data Register Empty Interrupts
	// UCSR0B &= ~((1 << TXCIE0) | (1 << UDRIE0));
}

// Receive Complete Interrupt Request
ISR(USART_RX_vect)
{
	// Copy Received Data From UDR
	*USART_ReceivedData++ = UDR0;

	if (--USART_ReceivedDataSize == 0)
		// Disable Receive Complete Interrupt
		UCSR0B &= ~(1 << RXCIE0);
}