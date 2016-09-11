/*
 * Alarm-AT328P-ArduinoUNO.cpp
 *
 * Created: 09/09/2016 18:18:36
 * Author : perma
 */ 

#define F_CPU = 8000000;

#include <avr/io.h>
#include "IOShieldKA05.h"

int main(void)
{
    IOShieldKA05 shield;
	shield.Init( false );
	
	shield.EnableAD();
	
	int outputCount = 6;
	uint16_t stepSize = 1023 / outputCount;
	
	while(true) {
		uint16_t value = shield.ReadAD( 0 );
		// Activate output based on either the corresponding digital input or the
		// level of the first analog input.
		for( int i = 0; i <= outputCount; ++ i ) {
			if( shield.ReadInput( i ) || value > stepSize * i ) {
				shield.SetOutput( i );
			}
			else {
				shield.ClearOutput( i );
			}
		}		
	}		
}

