/* 
* RS232.h
*
* Created: 12/09/2016 19:29:06
* Author: perma
*/

#pragma once
#include <stddef.h>

// In C++ Compiler -> misc -> other flags: -DF_CPU=16000000 -DBAUD=115200
#include <util/setbaud.h>
#include <avr/io.h>

class RS232
{

public:
	RS232();
	~RS232();
	
	void Enable();
		
	void Write( uint8_t b );
	void Write( uint8_t* data, size_t length );
	uint8_t Read();
	
protected:
private:
	RS232( const RS232 &c ) = delete;
	RS232& operator=( const RS232 &c ) = delete;

}; //RS232
