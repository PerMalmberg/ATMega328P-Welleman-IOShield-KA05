/*
 * Alarm-AT328P-ArduinoUNO.cpp
 *
 * Created: 09/09/2016 18:18:36
 * Author : perma
 */ 

#include "RS232.h"

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "IOShieldKA05.h"


int main(void)
{
    IOShieldKA05 shield;
	shield.Init( false );
	shield.EnableAD();
		
	RS232 serial;
	serial.Enable();
		
	char buff[20];
	bool digital[shield.GetDigitalInputCount()];
	uint16_t analog[shield.GetDigitalInputCount()];
	bool sendFullUpdate = true;
	uint16_t count = 0;
	
	while(true) {		
		for( int i = 0; i < shield.GetDigitalInputCount(); ++i) {
			bool state = shield.ReadInput( i );
			if( sendFullUpdate || state != digital[i] ) {
				sprintf( buff, "{\"DI%d\":\"%d\"}\r\n", i, state ? 1 : 0 );
				serial.Write( reinterpret_cast<uint8_t*>( &buff[0] ), strlen(buff) );
			}
			digital[i] = state;
		}
		
		for( int i = 0; i < shield.GetAnalogInputCount(); ++i) {
			volatile uint16_t value = shield.ReadAD( i );
			if( sendFullUpdate || abs( value - analog[i] ) > 3 ) {			
				sprintf( buff, "{\"AI%d\":\"%d\"}\r\n", i, value );
				serial.Write( reinterpret_cast<uint8_t*>( &buff[0] ), strlen(buff) );
			}
			analog[i] = value;				
		}
		              
		if( ++count > 10000 ) {
			count = 0;
			sendFullUpdate = true;
			// In case the communication has gone out-of-synch, stop sending for
			// a short while before each update so that the TX line is held high.
			_delay_ms(500);		
		}
		else {
			sendFullUpdate = false;	
		}	
	}
}

