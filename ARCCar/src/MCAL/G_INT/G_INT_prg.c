#include <avr/io.h>
#include "G_INT_int.h"

void G_INT_Enable()
{
	SREG |= (1 << SREG_I);
}

void G_INT_Disable()
{
	SREG &= ~(1 << SREG_I);
}
