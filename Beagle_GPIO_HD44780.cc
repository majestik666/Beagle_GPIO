/******************************
 ** Beagle Bone GPIO Library **
 **                          **
 **      Francois Sugny      **
 **         01/07/12         **
 **                          **
 **          v1.0            ** 
 ******************************/
 
//=======================================================
//=======================================================

#include <stdlib.h>
#include <string.h>

#include "Beagle_GPIO_HD44780.hh"

//=======================================================
//=======================================================

Beagle_GPIO_HD44780::Beagle_GPIO_HD44780(
		Beagle_GPIO * gpio,
		unsigned short _pin_E,
		unsigned short _pin_RS,
		unsigned short _pin_DB4,
		unsigned short _pin_DB5,
		unsigned short _pin_DB6,
		unsigned short _pin_DB7)
{
	if (!gpio || !gpio->isActive())
	{
		GPIO_ERROR( "Invalid or Inactive GPIO Module" );
		m_gpio = NULL;
		return;
	}
	m_gpio = gpio;

	m_pin_E = _pin_E;
	m_pin_RS = _pin_RS;
	m_pin_DB4 = _pin_DB4;
	m_pin_DB5 = _pin_DB5;
	m_pin_DB6 = _pin_DB6;
	m_pin_DB7 = _pin_DB7;

	// Initialize pins on the board
	gpio->configurePin( m_pin_E, Beagle_GPIO::kOUTPUT );
	gpio->enablePinInterrupts( m_pin_E, false );
	gpio->configurePin( m_pin_RS, Beagle_GPIO::kOUTPUT );
	gpio->enablePinInterrupts( m_pin_RS, false );
	gpio->configurePin( m_pin_DB4, Beagle_GPIO::kOUTPUT );
	gpio->enablePinInterrupts( m_pin_DB4, false );
	gpio->configurePin( m_pin_DB5, Beagle_GPIO::kOUTPUT );
	gpio->enablePinInterrupts( m_pin_DB5, false );
	gpio->configurePin( m_pin_DB6, Beagle_GPIO::kOUTPUT );
	gpio->enablePinInterrupts( m_pin_DB6, false );
	gpio->configurePin( m_pin_DB7, Beagle_GPIO::kOUTPUT );
	gpio->enablePinInterrupts( m_pin_DB7, false );

	m_gpio->writePin( m_pin_E, 0);
	m_gpio->writePin( m_pin_RS, 0);
	m_gpio->writePin( m_pin_DB4, 0);
	m_gpio->writePin( m_pin_DB5, 0);
	m_gpio->writePin( m_pin_DB6, 0);
	m_gpio->writePin( m_pin_DB7, 0);
}

//=======================================================
//=======================================================

Beagle_GPIO_HD44780::~Beagle_GPIO_HD44780()
{
	GPIO_PRINT( "Closing LCD Screen" );
	// Close Screen
	writeToPins( 0, 0, 1, 1, 0, 0 );
	//
	m_gpio = NULL;
}

//=======================================================
//=======================================================

// Pulse pin E
void Beagle_GPIO_HD44780::pulsePinE()
{
	m_gpio->writePin( m_pin_E, 1 );
	usleep(1000);
	m_gpio->writePin( m_pin_E, 0 );
	usleep(10000);
}

//=======================================================
//=======================================================

// Write data to the pins
void Beagle_GPIO_HD44780::writeToPins( 
		unsigned char _E,
		unsigned char _RS,
		unsigned char _DB4,
		unsigned char _DB5,
		unsigned char _DB6,
		unsigned char _DB7 )
{
	m_gpio->writePin( m_pin_E, _E);
	m_gpio->writePin( m_pin_RS, _RS);
	m_gpio->writePin( m_pin_DB4, _DB4);
	m_gpio->writePin( m_pin_DB5, _DB5);
	m_gpio->writePin( m_pin_DB6, _DB6);
	m_gpio->writePin( m_pin_DB7, _DB7);
	pulsePinE();
}

//=======================================================
//=======================================================

// Initialize Screen
void Beagle_GPIO_HD44780::initScreen()
{
	GPIO_PRINT( "Initializing HD44780 Screen" );
	// Wait before init 100ms
	sleep(1.0);

	// Write Pins
	writeToPins( 0, 0, 1, 1, 0, 0 );
	usleep(50000);

	// Write Pins
	writeToPins( 0, 0, 1, 1, 0, 0 );
	usleep(2000);

	// Write Pins
	writeToPins( 0, 0, 1, 1, 0, 0 );
	usleep(2000);

	// Write Pins = 4bits mode
	writeToPins( 0, 0, 0, 1, 0, 0 );
	usleep(50000);

	sendCommand( 0x28 );
	sendCommand( 0x08 );
	sendCommand( 0x01 );
	sendCommand( 0x06 );
	sendCommand( 0x0C );

	GPIO_PRINT( "HD44780 Screen Initialized" );
}

//=======================================================
//=======================================================

// Clear Screen
void Beagle_GPIO_HD44780::clearScreen()
{
	sendCommand( 0x01 );
}

//=======================================================
//=======================================================

// Write a string to screen
void Beagle_GPIO_HD44780::write( const char * _string )
{
	int l = strlen( _string );
	for ( int i=0; i<l; ++i)
		sendChar( _string[i] );
}

//=======================================================
//=======================================================

// Send a command to screen
void Beagle_GPIO_HD44780::sendCommand( char _c )
{
	// Send high 4 bits
	writeToPins( 0, 0, (_c & 0x10) >> 4, (_c & 0x20) >> 5, (_c & 0x40) >> 6, (_c & 0x80) >> 7 );
	// Send low 4 bits
	writeToPins( 0, 0, _c & 0x01,  (_c & 0x02) >> 1, (_c & 0x04) >> 2, (_c & 0x08) >> 3 );
}

//=======================================================
//=======================================================

// Write a character to screen
void Beagle_GPIO_HD44780::sendChar( char _c )
{
	// Send high 4 bits
	writeToPins( 0, 1, (_c & 0x10) >> 4, (_c & 0x20) >> 5, (_c & 0x40) >> 6, (_c & 0x80) >> 7 );
	// Send low 4 bits
	writeToPins( 0, 1, _c & 0x01,  (_c & 0x02) >> 1, (_c & 0x04) >> 2, (_c & 0x08) >> 3 );
}

//=======================================================
//=======================================================

// Move to a specific position on screen
void Beagle_GPIO_HD44780::goToPosition( unsigned char _x, unsigned char _y )
{
	unsigned char address = _x-1 + _y * 0x40 + 0x80;
	sendCommand( address );
}

//=======================================================
//=======================================================

// Turn cursor on/off and blink/solid
void Beagle_GPIO_HD44780::setCursor( bool enable, bool blink)
{
	unsigned char cmd = 0x0C;
	if ( enable )
		cmd += 0x02;
	if ( blink )
		cmd += 0x1;
	sendCommand( cmd );
}

//=======================================================
//=======================================================


