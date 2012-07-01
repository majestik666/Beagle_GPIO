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
 
#ifndef beagle_gpio_KS0108_hh
#define beagle_gpio_KS0108_hh
 
//=======================================================
//=======================================================

#include "Beagle_GPIO.hh"

//=======================================================
//=======================================================

class Beagle_GPIO_KS0108
{
public:
	Beagle_GPIO_KS0108(
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
			unsigned short _pin_CS3 );

	~Beagle_GPIO_KS0108();

	// Initialize Screen
	void initScreen();

	// Clear Screen
	void clearScreen();

	// Write a string to screen
	void write( const char * _string );

	// Move to a specific position on screen
	void goToPosition( unsigned char _x, unsigned char _y );

	// Write a single pixel
	void setPixel( unsigned char _x, unsigned char _y, unsigned char _c );

private:
	// Write some data
	void writeData( unsigned char _c );

	// Read some data
	unsigned char readData();

	// Write a character
	void writeChar( unsigned char _c );

	// Write a command
	void writeCommand( unsigned char _c, unsigned char _d );

	// Enable Controller
	void enableController( unsigned char _controller );

	// Disable Controller
	void disableController( unsigned char _controller );

	// Set Data Port as Output
	void setDataPortAsOutput();

	// Set Data Port as Input
	void setDataPortAsInput();

	// Read Data Port
	unsigned char readDataPort();

	// Write Data Port
	void writeDataPort( unsigned char _c );

	// Read screen status
	unsigned char readStatus( unsigned char _controller );


private:
	Beagle_GPIO * 	m_gpio;
	unsigned short 	m_pin_RS;
	unsigned short 	m_pin_RW;
	unsigned short 	m_pin_E;
	unsigned short 	m_pin_DB0;
	unsigned short 	m_pin_DB1;
	unsigned short 	m_pin_DB2;
	unsigned short 	m_pin_DB3;
	unsigned short 	m_pin_DB4;
	unsigned short 	m_pin_DB5;
	unsigned short 	m_pin_DB6;
	unsigned short 	m_pin_DB7;
	unsigned short 	m_pin_CS1;
	unsigned short 	m_pin_CS2;
	unsigned short 	m_pin_CS3;
	unsigned short 	m_pin_RST;

	unsigned char 	m_screenX;
	unsigned char 	m_screenY;
};

//=======================================================
//=======================================================

#endif

//=======================================================
//=======================================================
