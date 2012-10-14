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

//=======================================================
//=======================================================

#include "Beagle_GPIO_Nokia6100.hh"

//=======================================================
//=======================================================

// Array storing the font
const unsigned char Beagle_GPIO_Nokia6100::font_5x8[] = 
{
	0x00, 0x00, 0x00, 0x00, 0x00, // (space)
	0x00, 0x00, 0x5F, 0x00, 0x00, // !
	0x00, 0x07, 0x00, 0x07, 0x00, // "
	0x14, 0x7F, 0x14, 0x7F, 0x14, // #
	0x24, 0x2A, 0x7F, 0x2A, 0x12, // $
	0x23, 0x13, 0x08, 0x64, 0x62, // %
	0x36, 0x49, 0x55, 0x22, 0x50, // &
	0x00, 0x05, 0x03, 0x00, 0x00, // '
	0x00, 0x1C, 0x22, 0x41, 0x00, // (
	0x00, 0x41, 0x22, 0x1C, 0x00, // )
	0x08, 0x2A, 0x1C, 0x2A, 0x08, // *
	0x08, 0x08, 0x3E, 0x08, 0x08, // +
	0x00, 0x50, 0x30, 0x00, 0x00, // ,
	0x08, 0x08, 0x08, 0x08, 0x08, // -
	0x00, 0x30, 0x30, 0x00, 0x00, // .
	0x20, 0x10, 0x08, 0x04, 0x02, // /
	0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
	0x00, 0x42, 0x7F, 0x40, 0x00, // 1
	0x42, 0x61, 0x51, 0x49, 0x46, // 2
	0x21, 0x41, 0x45, 0x4B, 0x31, // 3
	0x18, 0x14, 0x12, 0x7F, 0x10, // 4
	0x27, 0x45, 0x45, 0x45, 0x39, // 5
	0x3C, 0x4A, 0x49, 0x49, 0x30, // 6
	0x01, 0x71, 0x09, 0x05, 0x03, // 7
	0x36, 0x49, 0x49, 0x49, 0x36, // 8
	0x06, 0x49, 0x49, 0x29, 0x1E, // 9
	0x00, 0x36, 0x36, 0x00, 0x00, // :
	0x00, 0x56, 0x36, 0x00, 0x00, // ;
	0x00, 0x08, 0x14, 0x22, 0x41, // <
	0x14, 0x14, 0x14, 0x14, 0x14, // =
	0x41, 0x22, 0x14, 0x08, 0x00, // >
	0x02, 0x01, 0x51, 0x09, 0x06, // ?
	0x32, 0x49, 0x79, 0x41, 0x3E, // @
	0x7E, 0x11, 0x11, 0x11, 0x7E, // A
	0x7F, 0x49, 0x49, 0x49, 0x36, // B
	0x3E, 0x41, 0x41, 0x41, 0x22, // C
	0x7F, 0x41, 0x41, 0x22, 0x1C, // D
	0x7F, 0x49, 0x49, 0x49, 0x41, // E
	0x7F, 0x09, 0x09, 0x01, 0x01, // F
	0x3E, 0x41, 0x41, 0x51, 0x32, // G
	0x7F, 0x08, 0x08, 0x08, 0x7F, // H
	0x00, 0x41, 0x7F, 0x41, 0x00, // I
	0x20, 0x40, 0x41, 0x3F, 0x01, // J
	0x7F, 0x08, 0x14, 0x22, 0x41, // K
	0x7F, 0x40, 0x40, 0x40, 0x40, // L
	0x7F, 0x02, 0x04, 0x02, 0x7F, // M
	0x7F, 0x04, 0x08, 0x10, 0x7F, // N
	0x3E, 0x41, 0x41, 0x41, 0x3E, // O
	0x7F, 0x09, 0x09, 0x09, 0x06, // P
	0x3E, 0x41, 0x51, 0x21, 0x5E, // Q
	0x7F, 0x09, 0x19, 0x29, 0x46, // R
	0x46, 0x49, 0x49, 0x49, 0x31, // S
	0x01, 0x01, 0x7F, 0x01, 0x01, // T
	0x3F, 0x40, 0x40, 0x40, 0x3F, // U
	0x1F, 0x20, 0x40, 0x20, 0x1F, // V
	0x7F, 0x20, 0x18, 0x20, 0x7F, // W
	0x63, 0x14, 0x08, 0x14, 0x63, // X
	0x03, 0x04, 0x78, 0x04, 0x03, // Y
	0x61, 0x51, 0x49, 0x45, 0x43, // Z
	0x00, 0x00, 0x7F, 0x41, 0x41, // [
	0x02, 0x04, 0x08, 0x10, 0x20, // "\"
	0x41, 0x41, 0x7F, 0x00, 0x00, // ]
	0x04, 0x02, 0x01, 0x02, 0x04, // ^
	0x40, 0x40, 0x40, 0x40, 0x40, // _
	0x00, 0x01, 0x02, 0x04, 0x00, // `
	0x20, 0x54, 0x54, 0x54, 0x78, // a
	0x7F, 0x48, 0x44, 0x44, 0x38, // b
	0x38, 0x44, 0x44, 0x44, 0x20, // c
	0x38, 0x44, 0x44, 0x48, 0x7F, // d
	0x38, 0x54, 0x54, 0x54, 0x18, // e
	0x08, 0x7E, 0x09, 0x01, 0x02, // f
	0x08, 0x14, 0x54, 0x54, 0x3C, // g
	0x7F, 0x08, 0x04, 0x04, 0x78, // h
	0x00, 0x44, 0x7D, 0x40, 0x00, // i
	0x20, 0x40, 0x44, 0x3D, 0x00, // j
	0x00, 0x7F, 0x10, 0x28, 0x44, // k
	0x00, 0x41, 0x7F, 0x40, 0x00, // l
	0x7C, 0x04, 0x18, 0x04, 0x78, // m
	0x7C, 0x08, 0x04, 0x04, 0x78, // n
	0x38, 0x44, 0x44, 0x44, 0x38, // o
	0x7C, 0x14, 0x14, 0x14, 0x08, // p
	0x08, 0x14, 0x14, 0x18, 0x7C, // q
	0x7C, 0x08, 0x04, 0x04, 0x08, // r
	0x48, 0x54, 0x54, 0x54, 0x20, // s
	0x04, 0x3F, 0x44, 0x40, 0x20, // t
	0x3C, 0x40, 0x40, 0x20, 0x7C, // u
	0x1C, 0x20, 0x40, 0x20, 0x1C, // v
	0x3C, 0x40, 0x30, 0x40, 0x3C, // w
	0x44, 0x28, 0x10, 0x28, 0x44, // x
	0x0C, 0x50, 0x50, 0x50, 0x3C, // y
	0x44, 0x64, 0x54, 0x4C, 0x44, // z
	0x00, 0x08, 0x36, 0x41, 0x00, // {
	0x00, 0x00, 0x7F, 0x00, 0x00, // |
	0x00, 0x41, 0x36, 0x08, 0x00, // }
	0x08, 0x08, 0x2A, 0x1C, 0x08, // ->
	0x08, 0x1C, 0x2A, 0x08, 0x08 // <-
};

//=======================================================
//=======================================================

Beagle_GPIO_Nokia6100::Beagle_GPIO_Nokia6100(
		Beagle_GPIO * gpio,
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

	m_use_SPI = 0;

	m_pin_CS    = _pin_CS;
	m_pin_SCLK  = _pin_SCLK;
	m_pin_SDATA = _pin_SDATA;
	m_pin_RESET = _pin_RESET;

	// Initialize pins on the board
	gpio->configurePin( m_pin_CS,    Beagle_GPIO::kOUTPUT );
	gpio->configurePin( m_pin_SCLK,  Beagle_GPIO::kOUTPUT );
	gpio->configurePin( m_pin_SDATA, Beagle_GPIO::kOUTPUT );
	gpio->configurePin( m_pin_RESET, Beagle_GPIO::kOUTPUT );
	m_gpio->writePin( m_pin_CS,    1);
	m_gpio->writePin( m_pin_SCLK,  0);
	m_gpio->writePin( m_pin_SDATA, 0);
	m_gpio->writePin( m_pin_RESET, 1);
}

//=======================================================
//=======================================================

Beagle_GPIO_Nokia6100::Beagle_GPIO_Nokia6100(
		Beagle_GPIO * gpio,
		unsigned short _pin_RESET )
{
	if (!gpio || !gpio->isActive())
	{
		GPIO_ERROR( "Invalid or Inactive GPIO Module" );
		m_gpio = NULL;
		return;
	}
	m_gpio = gpio;

	m_use_SPI = 1;
	m_spi_buffer = new unsigned char[65536];

	m_spi_buffer_index = 0;
	// Mode 0, 9bits, 48000kHz, 0 delay
	m_gpio->openSPI( 0, 9, 48000000, 0 );

	m_pin_RESET = _pin_RESET;

	// Initialize pins on the board
	gpio->configurePin( m_pin_RESET, Beagle_GPIO::kOUTPUT );
	m_gpio->writePin( m_pin_RESET, 1);
}

//=======================================================
//=======================================================

Beagle_GPIO_Nokia6100::~Beagle_GPIO_Nokia6100()
{
	if ( m_use_SPI )
	{
		m_gpio->closeSPI();
		delete [] m_spi_buffer;
		m_spi_buffer_index = 0;
	}
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
		m_gpio->writePin( m_pin_SCLK,  1);
	}
}

//=======================================================
//=======================================================

// Send a command to the screen
void Beagle_GPIO_Nokia6100::sendCommand( unsigned char _cmd )
{
	m_gpio->writePin( m_pin_SDATA, 0);
	m_gpio->writePin( m_pin_SCLK, 0);
	m_gpio->writePin( m_pin_SCLK, 1);

	shiftBits( _cmd );
}

//=======================================================
//=======================================================

// Send data to the screen
void Beagle_GPIO_Nokia6100::sendData( unsigned char _data )
{
	m_gpio->writePin( m_pin_SDATA, 1);
	m_gpio->writePin( m_pin_SCLK, 0);
	m_gpio->writePin( m_pin_SCLK, 1);

	shiftBits( _data );
}

//=======================================================
//=======================================================

// Initialize Screen
void Beagle_GPIO_Nokia6100::initScreen()
{
	GPIO_PRINT( "Initializing Nokia6100 Screen" );

	if ( !m_use_SPI )
	{	
		// Regular non-SPI Init
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

		clearScreen();

		sendCommand( kDISON );

		usleep(100000);
	}
	else
	{	
		// SPI Init
		// Perform a reset
		m_gpio->writePin( m_pin_RESET, 1 );
		usleep(10000);
		m_gpio->writePin( m_pin_RESET, 0 );
		usleep(10000);
		m_gpio->writePin( m_pin_RESET, 1 );
		usleep(10000);

		addSPICommand( kDISCTL );
		addSPIData( 0x0C );
		addSPIData( 0x20 );
		addSPIData( 0x00 );
		addSPIData( 0x01 );

		addSPICommand( kDISCTL );
		addSPIData( 0x0C );
		addSPIData( 0x20 );
		addSPIData( 0x00 );
		addSPIData( 0x01 );

		addSPICommand( kCOMSCN );
		addSPIData( 0x01 );

		addSPICommand( kOSCON );
		addSPICommand( kSLPOUT );

		addSPICommand( kPWRCTR );
		addSPIData( 0x0F );

		addSPICommand( kDISINV );

		addSPICommand( kDATCTL );
		addSPIData( 0x00 );
		addSPIData( 0x00 );
		addSPIData( 0x02 );

		addSPICommand( kVOLCTR );
		addSPIData( 0x20 );
		addSPIData( 0x03 );

		addSPICommand( kNOP );

		sendSPIBuffer();

		usleep(100000);

		clearScreen();

		addSPICommand( kDISON );
		sendSPIBuffer();

		usleep(100000);
	}

	GPIO_PRINT( "Nokia6100 Screen Initialized" );
}

//=======================================================
//=======================================================

// Clear Screen
void Beagle_GPIO_Nokia6100::clearScreen()
{
	fillBox(0,0,132,132,0,0,0);
}

//=======================================================
//=======================================================

// Set window on display
void Beagle_GPIO_Nokia6100::setWindow( unsigned char _x1, unsigned char _y1, unsigned char _x2, unsigned char _y2 )
{
	if ( !m_use_SPI)
	{
		sendCommand( kPASET );
		sendData( _y1 + 2 );
		sendData( _y2 + 2 );

		sendCommand( kCASET );
		sendData( _x1 );
		sendData( _x2 );
	}
	else
	{
		addSPICommand( kPASET );
		addSPIData( _y1 + 2 );
		addSPIData( _y2 + 2 );

		addSPICommand( kCASET );
		addSPIData( _x1 );
		addSPIData( _x2 );

		sendSPIBuffer();
	}
}

//=======================================================
//=======================================================

// Write a single pixel
void Beagle_GPIO_Nokia6100::setPixel( unsigned char _x, unsigned char _y, unsigned char _r, unsigned char _g, unsigned char _b )
{
	setWindow( _x,_y,_x,_y);

	if ( !m_use_SPI )
	{
		sendCommand( kRAMWR );
		unsigned char _c = (_r << 4) | (_g >> 4);
		sendData( _c );
		_c = (_b << 4) | (_r >> 4);
		sendData( _c );
		_c = (_g << 4) | (_b >> 4);
		sendData( _c );
	}
	else
	{
		addSPICommand( kRAMWR );
		unsigned char _c = (_r << 4) | (_g >> 4);
		addSPIData( _c );
		_c = (_b << 4) | (_r >> 4);
		addSPIData( _c );
		_c = (_g << 4) | (_b >> 4);
		addSPIData( _c );
		sendSPIBuffer();
	}
}

//=======================================================
//=======================================================

// Fill a box on screen
void Beagle_GPIO_Nokia6100::fillBox( unsigned char _x1, unsigned char _y1, unsigned char _x2, unsigned char _y2, unsigned char _r, unsigned char _g, unsigned char _b )
{
	setWindow( _x1, _y1, _x2, _y2 );

	unsigned char b1 = (_r << 4) + (_g >> 4);
	unsigned char b2 = (_b << 4) + (_r >> 4);
	unsigned char b3 = (_g << 4) + (_b >> 4);

	int total_words = ((_x2-_x1+1)*(_y2-_y1+1)+1)/2;

	if ( !m_use_SPI )
	{
		sendCommand( kRAMWR );
		for (int i=0;i<total_words;++i)
		{
			sendData(b1);
			sendData(b2);
			sendData(b3);
		}
	}
	else
	{
		addSPICommand( kRAMWR );
		for (int i=0;i<total_words;++i)
		{
			addSPIData(b1);
			addSPIData(b2);
			addSPIData(b3);
			if (m_spi_buffer_index > 150)
				sendSPIBuffer();
		}
		// Send the reminder of the data
		sendSPIBuffer();
	}
}

//=======================================================
//=======================================================

// Write a pair of pixels at a time
void Beagle_GPIO_Nokia6100::writePair( unsigned char _r1,
				       unsigned char _g1,
				       unsigned char _b1,
				       unsigned char _r2,
				       unsigned char _g2,
				       unsigned char _b2 )
{
	unsigned char c1 = (_r1<<4) | (_g1>>4);
	unsigned char c2 = (_b1<<4) | (_r2>>4);
	unsigned char c3 = (_g2<<4) | (_b2>>4);
	if ( !m_use_SPI )
	{
		sendData( c1 );
		sendData( c2 );
		sendData( c3 );
	}
	else
	{
		addSPIData( c1 );
		addSPIData( c2 );
		addSPIData( c3 );
		sendSPIBuffer();
	}
}

//=======================================================
//=======================================================

// Write a string to screen
void Beagle_GPIO_Nokia6100::print( unsigned char _x,
				   unsigned char _y,
				   const char * _string,
				   unsigned char _r,
				   unsigned char _g,
				   unsigned char _b)
{
	while( *_string )
	{
		printChar( _x, _y, *_string, _r,_g,_b );
		_x += 6;
		_string++;
	};
}

//=======================================================
//=======================================================

// Write a single character
void Beagle_GPIO_Nokia6100::printChar( unsigned char _x, 
				       unsigned char _y,
				       char _c,
				       unsigned char _r,
				       unsigned char _g,
				       unsigned char _b )
{
	// Calculate index in font array
	int index = _c - ' ';
	if (index<0 || index>96)
		index = 0;

	// Get pointer to charachter data
	unsigned char * char_data = (unsigned char *)(font_5x8 + index*5);

	// Set the write window to the character size
	setWindow( _x,_y, _x+4,_y+8 );
	if ( !m_use_SPI )
	{
		sendCommand( kRAMWR );
	}
	else
	{
		addSPICommand( kRAMWR );
		sendSPIBuffer();
	}
	
	unsigned char b1,b2;
	// Write the character
	for (int j=0;j<8;++j)
	{
		unsigned char mask = 0x01 << j;
		for (int i=0;i<3;++i)
		{
			b1 = char_data[i*2] & mask;
			b2 = (i==2) ? 0 : char_data[i*2+1] & mask;

			writePair( b1 ? _r : 0, b1 ? _g : 0, b1 ? _b : 0,
				   b2 ? _r : 0, b2 ? _g : 0, b2 ? _b : 0 );
		}
	}
}

//=======================================================
//=======================================================

// Add a command to the SPI Buffer
void Beagle_GPIO_Nokia6100::addSPICommand( unsigned char _cmd )
{
	// Add a command to the buffer
	m_spi_buffer[m_spi_buffer_index++] = _cmd;
	m_spi_buffer[m_spi_buffer_index++] = 0x00;
}

//=======================================================
//=======================================================

// Add data to the SPI Buffe
void Beagle_GPIO_Nokia6100::addSPIData( unsigned char _data )
{
	// Add a data byte to the buffer
	m_spi_buffer[m_spi_buffer_index++] = _data;
	m_spi_buffer[m_spi_buffer_index++] = 0x01;
}

//=======================================================
//=======================================================

// Sends an SPI Buffer to screen
void Beagle_GPIO_Nokia6100::sendSPIBuffer()
{
	// Send what is in the buffer
	m_gpio->sendSPIBuffer( (unsigned long)(m_spi_buffer), m_spi_buffer_index );

	// Reset buffer index
	m_spi_buffer_index = 0;
}

//=======================================================
//=======================================================

// Write a buffer to screen
void Beagle_GPIO_Nokia6100::writeBuffer( unsigned char *buffer, unsigned char _x, unsigned char _y, unsigned char _w, unsigned char _h )
{
	// Set the window
	setWindow( _x, _y, _x+_w-1, _y+_h-1 );

	addSPICommand( kRAMWR );

	unsigned char b1,b2,b3;
	int total_words = (_w*_h+1)/2;
	int idx = 0;
	for (int i=0;i<total_words;++i,idx+=6)
	{
		b1 = (buffer[idx+0] << 4) + (buffer[idx+1] >> 4);	// r1,g1
		b2 = (buffer[idx+2] << 4) + (buffer[idx+3] >> 4);	// b1,r2
		b3 = (buffer[idx+4] << 4) + (buffer[idx+5] >> 4);	// g2,b2
		addSPIData(b1);
		addSPIData(b2);
		addSPIData(b3);
		if (m_spi_buffer_index > 150)
			sendSPIBuffer();
	}

	// Send the reminder
	sendSPIBuffer();
}

//=======================================================
//=======================================================

