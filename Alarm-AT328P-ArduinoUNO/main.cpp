/*
 * Alarm-AT328P-ArduinoUNO.cpp
 *
 * Created: 09/09/2016 18:18:36
 * Author : perma
 */ 

#include "RS232.h"

#include <avr/io.h>
#include <util/delay.h>
#include "IOShieldKA05.h"


int main(void)
{
    IOShieldKA05 shield;
	shield.Init( false );
	
	shield.EnableAD();
	
	int outputCount = 6;
	uint16_t stepSize = 1023 / outputCount;
	
	RS232 serial;
	
	while(true) {
		serial.Write( 'h' );
		serial.Write( 'e' );
		serial.Write( 'l' );
		serial.Write( 'l' );
		serial.Write( 'o' );
		_delay_ms(10);
		//uint8_t b = serial.Read();
		
		//int i = 0;
	}
	
	/*
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
	*/		
}

