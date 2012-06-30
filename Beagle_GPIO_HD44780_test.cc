
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

	// Init LCD screen
	lcd.initScreen();

	// Set cursor
	lcd.setCursor( false, false );

	// Clear Screen
	lcd.clearScreen();

	// Write a string to screen
	lcd.write( "test lcd" );

	lcd.goToPosition(5,1);
	lcd.write( "at pos" );

	sleep(2);
	lcd.setCursor( true, false );
	sleep(2);
	lcd.setCursor( true, true );
	sleep(2);
	lcd.setCursor( false, false );
	sleep(2);

	lcd.clearScreen();

	return 0;
}
