/* 
* IOShieldKA05.cpp
*
* Created: 09/09/2016 19:45:23
* Author: perma
*/


#include "IOShieldKA05.h"
#include <avr/io.h>

void
IOShieldKA05::Init( bool initalOutputState )
{
	// Setup ports
	
	// Configure digital inputs, with internal pull-up actived.
	// These ports are active-low, so ground them to activate.
	// PIND0 & PIND1 are the Rx/Tx for serial communication so we don't want to touch those.
	for( uint8_t pin = PIND2; pin <= PIND7; ++pin) {
		ConfigurePinAsInput(&DDRD, &PORTD, pin, false );
	}
	
	// Digital outputs
	for( uint8_t pin = PINB0; pin <= PINB5; ++pin ) {
		ConfigurePinAsOutput( &DDRB, &PORTB, pin, initalOutputState );
	}
	
	//DDRB = 0x00;
	//PORTB
	
	// Analog inputs
	// PORTD
}

void
IOShieldKA05::SetOutput( uint8_t output)
{
	if( IsValidOutput( output ) ) {
		SetBit( &PORTB, output );
	}
}

void
IOShieldKA05::ClearOutput( uint8_t output )
{
	if( IsValidOutput( output) ) {
		ClearBit( &PORTB, output );
	}
}


bool
IOShieldKA05::ReadInput( uint8_t input )
{
	bool res = false;
	
	input += PIND2; // Offset so that 'input 0' is the first input.
	
	if( input >= PIND2 && input <= PIND7 ) {
		res = ~PIND & ( 1 << input );
	}
	
	return res;
}

// default constructor
IOShieldKA05::IOShieldKA05()
{
} //IOShieldKA05

// default destructor
IOShieldKA05::~IOShieldKA05()
{
} //~IOShieldKA05

void 
IOShieldKA05::ConfigurePinAsInput( volatile uint8_t* DDRx, volatile uint8_t* PORTx, uint8_t pin, bool pullUpActive )
{
	ClearBit( DDRx, pin );
	if( pullUpActive ) {
		SetBit( PORTx, pin );
	}	
	else {
		ClearBit(PORTx, pin);
	}
}

void
IOShieldKA05::ConfigurePinAsOutput( volatile uint8_t* DDRx, volatile uint8_t* PORTx, uint8_t pin, bool initialState )
{
	SetBit( DDRx, pin );
	if( initialState ) {
		SetBit( PORTx, pin );
	}
	else {
		ClearBit( PORTx, pin );
	}
}

void
IOShieldKA05::SetBit( volatile uint8_t* port, uint8_t bit )
{
	*port |= 1 << bit;
}

void
IOShieldKA05::ClearBit( volatile uint8_t* port, uint8_t bit )
{
	*port &= ~(1 << bit);
}

bool 
IOShieldKA05::IsValidOutput( uint8_t output ) const 
{ 
	return output >= PINB0 && output < PINB6;
}

void
IOShieldKA05::Synchronize() const
{
	
	
}