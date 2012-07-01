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

#include "Beagle_GPIO_Nokia6100.hh"

//=======================================================
//=======================================================

Beagle_GPIO_Nokia6100::Beagle_GPIO_Nokia6100(
			Beagle_GPIO * gpio,
			unsigned short _pin_BL,
			unsigned short _pin_CS,
			unsigned short _pin_SCLK,
			unsigned short _pin_SDATA,
			unsigned short _pin_RESET )
{
	if (!gpio || !gpio->isActive())
	{
		GPIO_ERROR( "Invalid or Inactive GPIO Module" );
		m_gpio = NULL;
		return;
	}
	m_gpio = gpio;

	m_pin_BL    = _pin_BL;
	m_pin_CS    = _pin_CS;
	m_pin_SCLK  = _pin_SCLK;
	m_pin_SDATA = _pin_SDATA;
	m_pin_RESET = _pin_RESET;

	// Initialize pins on the board
	gpio->configurePin( m_pin_BL,    Beagle_GPIO::kOUTPUT );
	gpio->configurePin( m_pin_CS,    Beagle_GPIO::kOUTPUT );
	gpio->configurePin( m_pin_SCLK,  Beagle_GPIO::kOUTPUT );
	gpio->configurePin( m_pin_SDATA, Beagle_GPIO::kOUTPUT );
	gpio->configurePin( m_pin_RESET, Beagle_GPIO::kOUTPUT );
	m_gpio->writePin( m_pin_BL,    0);
	m_gpio->writePin( m_pin_CS,    1);
	m_gpio->writePin( m_pin_SCLK,  0);
	m_gpio->writePin( m_pin_SDATA, 0);
	m_gpio->writePin( m_pin_RESET, 1);
}

//=======================================================
//=======================================================

Beagle_GPIO_Nokia6100::~Beagle_GPIO_Nokia6100()
{
	GPIO_PRINT( "Closing LCD Screen" );
	m_gpio = NULL;
}

//=======================================================
//=======================================================

// Shift a byte to the screen
void Beagle_GPIO_Nokia6100::shiftBits( unsigned char _c )
{
	for (int i=7; i>=0; i--)
	{
		unsigned char bit = (_c & ( 0x01 << i ) ) >> i;
		m_gpio->writePin( m_pin_SDATA, bit);
		m_gpio->writePin( m_pin_SCLK,  0);
		//usleep(1);
		m_gpio->writePin( m_pin_SCLK,  1);
	}
}

//=======================================================
//=======================================================

// Send a command to the screen
void Beagle_GPIO_Nokia6100::sendCommand( unsigned char _cmd )
{
	//m_gpio->writePin( m_pin_CS, 0 );

	m_gpio->writePin( m_pin_SDATA, 0);
	m_gpio->writePin( m_pin_SCLK, 0);
	m_gpio->writePin( m_pin_SCLK, 1);

	shiftBits( _cmd );

	//m_gpio->writePin( m_pin_CS, 1 );
}

//=======================================================
//=======================================================

// Send data to the screen
void Beagle_GPIO_Nokia6100::sendData( unsigned char _data )
{
	//m_gpio->writePin( m_pin_CS, 0 );

	m_gpio->writePin( m_pin_SDATA, 1);
	m_gpio->writePin( m_pin_SCLK, 0);
	m_gpio->writePin( m_pin_SCLK, 1);

	shiftBits( _data );

	//m_gpio->writePin( m_pin_CS, 1 );
}

//=======================================================
//=======================================================

// Initialize Screen
void Beagle_GPIO_Nokia6100::initScreen()
{
	GPIO_PRINT( "Initializing Nokia6100 Screen" );
	
	m_gpio->writePin( m_pin_CS, 1 );
	m_gpio->writePin( m_pin_SDATA, 1 );
	m_gpio->writePin( m_pin_SCLK, 1 );

	// Perform a reset
	m_gpio->writePin( m_pin_RESET, 1 );
	usleep(10000);
	m_gpio->writePin( m_pin_RESET, 0 );
	usleep(10000);
	m_gpio->writePin( m_pin_RESET, 1 );
	usleep(10000);

	// Set CS 
	m_gpio->writePin( m_pin_CS, 0 );

	sendCommand( kDISCTL );
	sendData( 0x0C );
	sendData( 0x20 );
	sendData( 0x00 );
	sendData( 0x01 );

	sendCommand( kCOMSCN );
	sendData( 0x01 );

	sendCommand( kOSCON );
	sendCommand( kSLPOUT );

	sendCommand( kPWRCTR );
	sendData( 0x0F );

	sendCommand( kDISINV );

	sendCommand( kDATCTL );
	sendData( 0x00 );
	sendData( 0x00 );
	sendData( 0x02 );

	sendCommand( kVOLCTR );
	sendData( 0x20 );
	sendData( 0x03 );

	sendCommand( kNOP );

	usleep(100000);

	sendCommand( kDISON );

	usleep(100000);

	int p=0;
	unsigned char r,g,b;
	int total_words = (132*132+1)/2;
	while (1)
	{
		r = g = b = 0;
		if (p%1) { r|=0xF0; g|=0x0F; }
		if (p%2) { r|=0x0F; b|=0xF0; }
		if (p%3) { g|=0xF0; b|=0x0F; }
		setWindow( 0,0,132,132);
		sendCommand( kRAMWR );
		for (int i=0;i<total_words;++i)
		{
			sendData( r );
			sendData( g );
			sendData( b );
		}

		for (int i=0;i<128;++i)
			setPixel(i,i,i,i/2,i*2);
		for (int i=0;i<128;++i)
			for (int j=50;j<74;++j)	
				setPixel(i,j,0xFF,0,0);

		sleep(1);
		p++;
	}

	GPIO_PRINT( "Nokia6100 Screen Initialized" );
}

//=======================================================
//=======================================================

// Clear Screen
void Beagle_GPIO_Nokia6100::clearScreen()
{
}

//=======================================================
//=======================================================

// Set window on display
void Beagle_GPIO_Nokia6100::setWindow( unsigned char _x1, unsigned char _y1, unsigned char _x2, unsigned char _y2 )
{
	sendCommand( kPASET );
	sendData( _y1 + 2 );
	sendData( _y2 + 2 );

	sendCommand( kCASET );
	sendData( _x1 );
	sendData( _x2 );
}

//=======================================================
//=======================================================

// Write a single pixel
void Beagle_GPIO_Nokia6100::setPixel( unsigned char _x, unsigned char _y, unsigned char _r, unsigned char _g, unsigned char _b )
{
	setWindow( _x,_y,_x,_y);

	sendCommand( kRAMWR );
	unsigned char _c = (_r << 4) | (_g >> 4);
	sendData( _c );
	_c = _b << 4 | _r >> 4;
	sendData( _c );
	_c = _g << 4 | _b >> 4;
	sendData( _c );
}

//=======================================================
//=======================================================

// Write a string to screen
void Beagle_GPIO_Nokia6100::write( const char * _string )
{
}

//=======================================================
//=======================================================

