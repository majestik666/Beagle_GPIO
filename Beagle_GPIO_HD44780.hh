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
 
#ifndef beagle_gpio_hd44780_hh
#define beagle_gpio_hd44780_hh
 
//=======================================================
//=======================================================

#include "Beagle_GPIO.hh"

//=======================================================
//=======================================================

class Beagle_GPIO_HD44780
{
public:
	Beagle_GPIO_HD44780(
			Beagle_GPIO * gpio,
			unsigned short _pin_E,
			unsigned short _pin_RS,
			unsigned short _pin_DB4,
			unsigned short _pin_DB5,
			unsigned short _pin_DB6,
			unsigned short _pin_DB7 );
	~Beagle_GPIO_HD44780();

	// Initialize Screen
	void initScreen();

	// Clear Screen
	void clearScreen();

	// Write a string to screen
	void write( const char * _string );

	// Move to a specific position on screen
	void goToPosition( unsigned char _x, unsigned char _y );

	// Turn cursor on/off and blink/solid
	void setCursor( bool enable, bool blink);

private:
	// Pulse pin E
	void pulsePinE();

	// Write data to the pins
	void writeToPins( unsigned char _E,
			  unsigned char _RS,
			  unsigned char _DB4,
			  unsigned char _DB5,
			  unsigned char _DB6,
			  unsigned char _DB7 );

	// Write a character to screen
	void sendChar( char _c );

	// Send a command to screen
	void sendCommand( char _c );

private:
	Beagle_GPIO * 	m_gpio;
	unsigned short 	m_pin_E;
	unsigned short 	m_pin_RS;
	unsigned short 	m_pin_DB4;
	unsigned short 	m_pin_DB5;
	unsigned short 	m_pin_DB6;
	unsigned short 	m_pin_DB7;
};

//=======================================================
//=======================================================

#endif

//=======================================================
//=======================================================
