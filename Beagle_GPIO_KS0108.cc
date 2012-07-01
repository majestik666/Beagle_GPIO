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

#include "Beagle_GPIO_KS0108.hh"

//=======================================================
//=======================================================

Beagle_GPIO_KS0108::Beagle_GPIO_KS0108(
			Beagle_GPIO * gpio,
			unsigned short _pin_RS,
			unsigned short _pin_RW,
			unsigned short _pin_E,
			unsigned short _pin_DB0,
			unsigned short _pin_DB1,
			unsigned short _pin_DB2,
			unsigned short _pin_DB3,
			unsigned short _pin_DB4,
			unsigned short _pin_DB5,
			unsigned short _pin_DB6,
			unsigned short _pin_DB7,
			unsigned short _pin_CS1,
			unsigned short _pin_CS2,
			unsigned short _pin_CS3 )
{
	if (!gpio || !gpio->isActive())
	{
		GPIO_ERROR( "Invalid or Inactive GPIO Module" );
		m_gpio = NULL;
		return;
	}
	m_gpio = gpio;

	m_pin_RS = _pin_RS;
	m_pin_RW = _pin_RW;
	m_pin_E = _pin_E;
	m_pin_DB0 = _pin_DB0;
	m_pin_DB1 = _pin_DB1;
	m_pin_DB2 = _pin_DB2;
	m_pin_DB3 = _pin_DB3;
	m_pin_DB4 = _pin_DB4;
	m_pin_DB5 = _pin_DB5;
	m_pin_DB6 = _pin_DB6;
	m_pin_DB7 = _pin_DB7;
	m_pin_CS1 = _pin_CS1;
	m_pin_CS2 = _pin_CS2;
	m_pin_CS3 = _pin_CS3;

	// Initialize pins on the board
	gpio->configurePin( m_pin_RS, Beagle_GPIO::kOUTPUT );
	gpio->configurePin( m_pin_RW, Beagle_GPIO::kOUTPUT );
	gpio->configurePin( m_pin_E, Beagle_GPIO::kOUTPUT );
	gpio->configurePin( m_pin_CS1, Beagle_GPIO::kOUTPUT );
	gpio->configurePin( m_pin_CS2, Beagle_GPIO::kOUTPUT );
	gpio->configurePin( m_pin_CS3, Beagle_GPIO::kOUTPUT );

	m_gpio->writePin( m_pin_RS, 0);
	m_gpio->writePin( m_pin_RW, 0);
	m_gpio->writePin( m_pin_E, 0);
	m_gpio->writePin( m_pin_DB0, 0);
	m_gpio->writePin( m_pin_DB1, 0);
	m_gpio->writePin( m_pin_DB2, 0);
	m_gpio->writePin( m_pin_DB3, 0);
	m_gpio->writePin( m_pin_DB4, 0);
	m_gpio->writePin( m_pin_DB5, 0);
	m_gpio->writePin( m_pin_DB6, 0);
	m_gpio->writePin( m_pin_DB7, 0);
	m_gpio->writePin( m_pin_CS1, 1);
	m_gpio->writePin( m_pin_CS2, 1);
	m_gpio->writePin( m_pin_CS3, 1);
}

//=======================================================
//=======================================================

Beagle_GPIO_KS0108::~Beagle_GPIO_KS0108()
{
	GPIO_PRINT( "Closing LCD Screen" );
	m_gpio = NULL;
}

//=======================================================
//=======================================================

// Initialize Screen
void Beagle_GPIO_KS0108::initScreen()
{
	GPIO_PRINT( "Initializing KS0108 Screen" );

	// Wait 100ms
	sleep( 0.1 );

	for ( int i=0; i<3; ++i )
		writeCommand( 0x3F, i );
	
	// Wait 100ms
	sleep( 0.1 );

	GPIO_PRINT( "KS0108 Screen Initialized" );
}

//=======================================================
//=======================================================

// Clear Screen
void Beagle_GPIO_KS0108::clearScreen()
{
	for ( int j=0; j<64; ++j )
	{
		goToPosition( 0, j );
		for ( int i=0; i<128; ++i )
			writeData( 0x00 );
	}
}

//=======================================================
//=======================================================

// Write a single pixel
void Beagle_GPIO_KS0108::setPixel( unsigned char _x, unsigned char _y, unsigned char _c )
{
	unsigned char tmp;
	goToPosition( _x, _y/8 );
	tmp = readData();
	goToPosition( _x, _y/8 );
	tmp = readData();
	goToPosition( _x, _y/8 );
	if ( _c )
		tmp |= ( 1 << ( _y % 8 ) );
	else
		tmp &= ~( 1 << ( _y % 8 ) );
	writeData( tmp );
}

//=======================================================
//=======================================================

// Enable Controller
void Beagle_GPIO_KS0108::enableController( unsigned char _controller )
{
	switch( _controller)
	{
		case 0: m_gpio->writePin( m_pin_CS1, 0 ); break;
		case 1: m_gpio->writePin( m_pin_CS2, 0 ); break;
		case 2: m_gpio->writePin( m_pin_CS3, 0 ); break;
	};
}

//=======================================================
//=======================================================

// Disable Controller
void Beagle_GPIO_KS0108::disableController( unsigned char _controller )
{
	switch( _controller)
	{
		case 0: m_gpio->writePin( m_pin_CS1, 1 ); break;
		case 1: m_gpio->writePin( m_pin_CS2, 1 ); break;
		case 2: m_gpio->writePin( m_pin_CS3, 1 ); break;
	};
}

//=======================================================
//=======================================================

// Set Data Port as Output
void Beagle_GPIO_KS0108::setDataPortAsOutput()
{
	m_gpio->configurePin( m_pin_DB0, Beagle_GPIO::kOUTPUT );
	m_gpio->configurePin( m_pin_DB1, Beagle_GPIO::kOUTPUT );
	m_gpio->configurePin( m_pin_DB2, Beagle_GPIO::kOUTPUT );
	m_gpio->configurePin( m_pin_DB3, Beagle_GPIO::kOUTPUT );
	m_gpio->configurePin( m_pin_DB4, Beagle_GPIO::kOUTPUT );
	m_gpio->configurePin( m_pin_DB5, Beagle_GPIO::kOUTPUT );
	m_gpio->configurePin( m_pin_DB6, Beagle_GPIO::kOUTPUT );
	m_gpio->configurePin( m_pin_DB7, Beagle_GPIO::kOUTPUT );
}

//=======================================================
//=======================================================

// Set Data Port as Input
void Beagle_GPIO_KS0108::setDataPortAsInput()
{
	m_gpio->configurePin( m_pin_DB0, Beagle_GPIO::kINPUT );
	m_gpio->configurePin( m_pin_DB1, Beagle_GPIO::kINPUT );
	m_gpio->configurePin( m_pin_DB2, Beagle_GPIO::kINPUT );
	m_gpio->configurePin( m_pin_DB3, Beagle_GPIO::kINPUT );
	m_gpio->configurePin( m_pin_DB4, Beagle_GPIO::kINPUT );
	m_gpio->configurePin( m_pin_DB5, Beagle_GPIO::kINPUT );
	m_gpio->configurePin( m_pin_DB6, Beagle_GPIO::kINPUT );
	m_gpio->configurePin( m_pin_DB7, Beagle_GPIO::kINPUT );
}

//=======================================================
//=======================================================

// Read Data Port
unsigned char Beagle_GPIO_KS0108::readDataPort()
{
	unsigned char result = 0x00;
	result += m_gpio->readPin( m_pin_DB0 );
	result += m_gpio->readPin( m_pin_DB1 ) << 1;
	result += m_gpio->readPin( m_pin_DB2 ) << 2;
	result += m_gpio->readPin( m_pin_DB3 ) << 3;
	result += m_gpio->readPin( m_pin_DB4 ) << 4;
	result += m_gpio->readPin( m_pin_DB5 ) << 5;
	result += m_gpio->readPin( m_pin_DB6 ) << 6;
	result += m_gpio->readPin( m_pin_DB7 ) << 7;

	return result;
}

//=======================================================
//=======================================================

// Write Data Port
void Beagle_GPIO_KS0108::writeDataPort( unsigned char _c )
{
	m_gpio->writePin( m_pin_DB0, (_c & 0x01) );
	m_gpio->writePin( m_pin_DB1, (_c & 0x02) >> 1 );
	m_gpio->writePin( m_pin_DB2, (_c & 0x04) >> 2 );
	m_gpio->writePin( m_pin_DB3, (_c & 0x08) >> 3 );
	m_gpio->writePin( m_pin_DB4, (_c & 0x10) >> 4 );
	m_gpio->writePin( m_pin_DB5, (_c & 0x20) >> 5 );
	m_gpio->writePin( m_pin_DB6, (_c & 0x40) >> 6 );
	m_gpio->writePin( m_pin_DB7, (_c & 0x80) >> 7 );
}

//=======================================================
//=======================================================

// Read screen status
unsigned char Beagle_GPIO_KS0108::readStatus( unsigned char _controller )
{
	// Set data port as input
	setDataPortAsInput();	
	
	// RW = 1
	m_gpio->writePin( m_pin_RW, 1 );

	// RS = 0
	m_gpio->writePin( m_pin_RS, 0 );

	// Enable Controller
	enableController( _controller );

	// E = 1
	m_gpio->writePin( m_pin_E, 1 );

	// wait 1ms
	usleep(1000);

	// Read Data Port
	unsigned char status = readDataPort();
	
	// E = 0
	m_gpio->writePin( m_pin_E, 0 );

	// Disable Controller
	disableController( _controller );

	return status;
}

//=======================================================
//=======================================================

// Write a string to screen
void Beagle_GPIO_KS0108::write( const char * _string )
{
	int l = strlen( _string );
	for ( int i=0; i<l; ++i)
		writeChar( _string[i] );
}

//=======================================================
//=======================================================

// Write a character
void Beagle_GPIO_KS0108::writeChar( unsigned char _c )
{
	_c -= 32;

	// Use Font Array to display character
}

//=======================================================
//=======================================================

// Move to a specific position on screen
void Beagle_GPIO_KS0108::goToPosition( unsigned char _x, unsigned char _y )
{
	m_screenX = _x;
	m_screenY = _y;
	for ( int i=0; i<128/64; ++i )
	{
		writeCommand( 0x40, i );
		writeCommand( 0xB8 | _y, i );
		writeCommand( 0xC0, i );	
	}

	writeCommand( 0x40 | (_x%64), (_x/64) );
	writeCommand( 0xB8 | _y, (_x/64) );
}

//=======================================================
//=======================================================

// Write some data
void Beagle_GPIO_KS0108::writeData( unsigned char _c )
{
	// Wait for controller busy flag
	while( readStatus( m_screenX/64 ) & 0x80 );

	// Set Data port as output
	setDataPortAsOutput();

	// RW=0 RS=1
	m_gpio->writePin( m_pin_RW, 0 );
	m_gpio->writePin( m_pin_RS, 1 );

	// Write command to Data Port
	writeDataPort( _c );

	// Enable controller
	enableController( m_screenX / 64 );

	// E = 1
	m_gpio->writePin( m_pin_E, 1 );

	// Delay
	usleep(1000);

	// E = 0
	m_gpio->writePin( m_pin_E, 0 );

	// Disable controller
	disableController( m_screenX / 64 );
}

//=======================================================
//=======================================================

// Read some data
unsigned char Beagle_GPIO_KS0108::readData()
{
	// Wait for controller busy flag
	while( readStatus( m_screenX/64 ) & 0x80 );

	// Set Data port as output
	setDataPortAsInput();

	// RW=1 RS=1
	m_gpio->writePin( m_pin_RW, 1 );
	m_gpio->writePin( m_pin_RS, 1 );

	// Enable controller
	enableController( m_screenX / 64 );

	// E = 1
	m_gpio->writePin( m_pin_E, 1 );

	// Delay
	usleep(1000);

	// Read actual data
	unsigned char result = readDataPort();

	// E = 0
	m_gpio->writePin( m_pin_E, 0 );

	// Disable controller
	disableController( m_screenX / 64 );

	// Advance position
	m_screenX++;

	return result;
}

//=======================================================
//=======================================================

// Write a command
void Beagle_GPIO_KS0108::writeCommand( unsigned char _c, unsigned char _controller )
{
	// Wait for controller busy flag
	while( readStatus(_controller) & 0x80 );

	// Set Data as output
	setDataPortAsOutput();

	// RW=0 RS=0
	m_gpio->writePin( m_pin_RW, 0 );
	m_gpio->writePin( m_pin_RS, 0 );

	// Enable controller
	enableController( _controller );

	// Write command to Data Port
	writeDataPort( _c );

	// E = 1
	m_gpio->writePin( m_pin_E, 1 );

	// Delay
	usleep(1000);

	// E = 0
	m_gpio->writePin( m_pin_E, 0 );

	// Disable controller
	disableController( _controller );
}

//=======================================================
//=======================================================

