
#include "Beagle_GPIO.hh"
#include "Beagle_GPIO_KS0108.hh"

#include <iostream>

Beagle_GPIO	gpio;

int main()
{
	GPIO_PRINT( "===========================" );
	GPIO_PRINT( "BeagleBone GPIO KS0108 Test" );
	GPIO_PRINT( "===========================" );

	Beagle_GPIO_KS0108 lcd(
			&gpio,
			Beagle_GPIO::P8_45,	// RS
			Beagle_GPIO::P8_44,	// RW
			Beagle_GPIO::P8_43,	// E
			Beagle_GPIO::P8_30,	// DB0
			Beagle_GPIO::P8_29,
			Beagle_GPIO::P8_28,
			Beagle_GPIO::P8_27,
			Beagle_GPIO::P8_26,
			Beagle_GPIO::P8_25,
			Beagle_GPIO::P8_24,
			Beagle_GPIO::P8_23,	// DB7
			Beagle_GPIO::P8_42,
			Beagle_GPIO::P8_41,
			Beagle_GPIO::P8_40 );

	// Init LCD screen
	lcd.initScreen();

	// Clear Screen
	//lcd.clearScreen();

	// Write a pixel
	lcd.setPixel( 20,30, 0xFF );

	// Write a string to screen
	lcd.goToPosition(3,0);
	lcd.write( "Beagle_GPIO" );

	lcd.goToPosition(3,1);
	lcd.write( "KS0108 Test" );

	//lcd.clearScreen();

	return 0;
}
