/* 
* IOShieldKA05.cpp
*
* Created: 09/09/2016 19:45:23
* Author: perma
*/


#include "IOShieldKA05.h"
#include <avr/io.h>

///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
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
}

///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
void
IOShieldKA05::SetOutput( uint8_t output)
{
	if( IsValidOutput( output ) ) {
		SetBit( &PORTB, output );
	}
}

///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
void
IOShieldKA05::ClearOutput( uint8_t output )
{
	if( IsValidOutput( output) ) {
		ClearBit( &PORTB, output );
	}
}

///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
uint16_t
IOShieldKA05::ReadAD( uint8_t channel )
{
	int16_t value = 0;
	
	// Single pass reading
	if( IsValidADChannel( channel ) ) {	
		// Select channel by setting lower nibble to the provided channel.
		ADMUX &= 0xF0;
		ADMUX |= channel; 
	
		// Enable Single Conversion
		SetBit( &ADCSRA, ADSC );
		
		// Wait for conversion to completion
		while( ADCSRA & (1 << ADSC) );
	
		// ADCL *must* be read first.
		value = ADCL;
		value |= ( (ADCH & 0x3) << 8); // Only two lower bits in use in ADCH.
	}
	
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
void
IOShieldKA05::EnableAD()
{
	// Since we are using PINS 23-28 as analogs pins we don't need to
	// call ConfigurePinAsInput( &DDRC, &PORTC, pin, false ). Instead, we
	// disable the digital input buffer for PORTC 
	DIDR0 = 0x00;
	
	// We want 10 bit precision, so prescaler must have a clock of < 250kHz.
	// This results in a 125kHz clock, i.e. 16MHz / 128 = 125KHz.
	ADCSRA |= ( 1 << ADPS2 ) | ( 1 << ADPS1 ) | ( 1 << ADPS0 );
	
	// Make sure value is right adjusted for 10 bit precision.
	ClearBit( &ADMUX, ADLAR );
	
	// Arduino UNO has an AVcc connected to 5V so we use that as a reference.
	ClearBit( &ADMUX, 7 );
	SetBit( &ADMUX, 6 );
	
	// Disable Auto Trigger
	ClearBit( &ADMUX, ADATE );
	
	// Disable ADC Interupt Enable
	ClearBit( &ADMUX, ADIE );
		
	// Disable power reduction for ADC
	ClearBit( &PRR, PRADC );
	
	// Enable analog-to-digital conversion
 	SetBit( &ADCSRA, ADEN );
}

///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
void
IOShieldKA05::DisableAD()
{
	ClearBit( &ADCSRA, ADEN );
}

///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
IOShieldKA05::IOShieldKA05()
{
} //IOShieldKA05

///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
IOShieldKA05::~IOShieldKA05()
{
} //~IOShieldKA05

///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
void
IOShieldKA05::SetBit( volatile uint8_t* port, uint8_t bit )
{
	*port |= 1 << bit;
}

///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
void
IOShieldKA05::ClearBit( volatile uint8_t* port, uint8_t bit )
{
	*port &= ~(1 << bit);
}

///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
bool 
IOShieldKA05::IsValidOutput( uint8_t output ) const 
{ 
	return output >= PINB0 && output < PINB6;
}

///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
bool
IOShieldKA05::IsValidADChannel( uint8_t channel ) const
{
	return channel >= ADC0D && channel <= ADC5D;	
}

///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
void
IOShieldKA05::Synchronize() const
{
	
	
}