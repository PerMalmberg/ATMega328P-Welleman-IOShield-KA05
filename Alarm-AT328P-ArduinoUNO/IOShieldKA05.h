/* 
* IOShieldKA05.h
*
* Created: 09/09/2016 19:45:23
* Author: perma
*/


#pragma once
#include <stdint.h>

// http://www.atmel.com/Images/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_datasheet.pdf

class IOShieldKA05
{
public:
	IOShieldKA05();
	~IOShieldKA05();
	void Init( bool initialState );
	
	// Sets the specified output, i.e. the relay is activated. Output is 0...5
	void SetOutput( uint8_t output);
	// Clears the specified output, i.e. the relay is deactivated. Output is 0...5
	void ClearOutput( uint8_t output );
	
	// Reads the specified input. Returns true if it is active (i.e. pulled low, to ground)
	// Input is 0...5
	bool ReadInput( uint8_t input );
	
protected:
private:
	IOShieldKA05( const IOShieldKA05 &c ) = delete;
	IOShieldKA05& operator=( const IOShieldKA05 &c ) = delete;

	void ConfigurePinAsInput( volatile uint8_t* DDRx, volatile uint8_t* PORTx, uint8_t pin, bool pullUpActive );
	void ConfigurePinAsOutput( volatile uint8_t* DDRx, volatile uint8_t* PORTx, uint8_t pin, bool initialState );
	void SetBit( volatile uint8_t* port, uint8_t bit );
	void ClearBit( volatile uint8_t* port, uint8_t bit );
	bool IsValidOutput( uint8_t output) const;
	void Synchronize() const;

}; //IOShieldKA05

