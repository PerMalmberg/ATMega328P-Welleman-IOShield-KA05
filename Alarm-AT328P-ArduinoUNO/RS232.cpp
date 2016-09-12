/* 
* RS232.cpp
*
* Created: 12/09/2016 19:29:05
* Author: perma
*/


#include "RS232.h"

void
RS232::Write( uint8_t b )
{
	while ( !(UCSR0A & (1 << UDRE0)) );
	UDR0 = b;
}

uint8_t
RS232::Read()
{
	while ( !(UCSR0A & (1 << RXC0)) );
	return UDR0;
}

RS232::RS232()
{
	UBRR0H = UBRRH_VALUE;	
	UBRR0L = UBRRL_VALUE;
	
#if USE_2X
	UCSR0A |= _BV(U2X0);
#else
	UCSR0A &= ~(_BV(U2X0));
#endif

	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}

RS232::~RS232()
{
}
