
#include "Beagle_GPIO.hh"
#include "Beagle_GPIO_HD44780.hh"

#include <iostream>

Beagle_GPIO	gpio;

int main()
{
	GPIO_PRINT( "============================" );
	GPIO_PRINT( "BeagleBone GPIO HD44780 Test" );
	GPIO_PRINT( "============================" );

	Beagle_GPIO_HD44780 lcd( &gpio, 
				 Beagle_GPIO::P8_45,
				 Beagle_GPIO::P8_44,
				 Beagle_GPIO::P8_43,
				 Beagle_GPIO::P8_42,
				 Beagle_GPIO::P8_41,
				 Beagle_GPIO::P8_40 );

	lcd.initScreen();


	// Clear Screen
	lcd.clearScreen();

	// Write a string to screen
	lcd.write( "test lcd" );

	sleep(5);

	lcd.clearScreen();

	return 0;
}
