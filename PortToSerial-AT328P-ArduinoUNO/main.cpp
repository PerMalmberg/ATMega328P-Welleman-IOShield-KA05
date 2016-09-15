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
#include "IOShieldKA05.h"


int main(void)
{
    IOShieldKA05 shield;
	shield.Init( false );
	shield.EnableAD();
		
	RS232 serial;
	serial.Enable();
		
	char buff[20];
		
	while(true) {
		for( int i = 0; i < shield.GetDigitalInputCount(); ++i) {
			bool state = shield.ReadInput( i );
			sprintf( buff, "{\"DI%d\":\"%d\"}\n", i, state ? 1 : 0 );
			serial.Write( reinterpret_cast<uint8_t*>( &buff[0] ), strlen(buff) );
		}
		
		for( int i = 0; i < shield.GetAnalogInputCount(); ++i) {
			uint8_t value = shield.ReadAD( i );
			sprintf( buff, "{\"AI%d\":\"%d\"}\n", i, value );
			serial.Write( reinterpret_cast<uint8_t*>( &buff[0] ), strlen(buff) );
		}
				
	}
}

