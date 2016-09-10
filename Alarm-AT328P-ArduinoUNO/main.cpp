/*
 * Alarm-AT328P-ArduinoUNO.cpp
 *
 * Created: 09/09/2016 18:18:36
 * Author : perma
 */ 

#include <avr/io.h>
#include "IOShieldKA05.h"

int main(void)
{
    IOShieldKA05 shield;
	shield.Init( false );
	
	while(true) {
		for( int i = 0; i < 6; ++i ) {
			if( shield.ReadInput(i) ) {
				shield.SetOutput(i);			
			}	
			else {
				shield.ClearOutput(i);			
			}	
		}
		
	}
}

