
#include "Beagle_GPIO.hh"
#include "Beagle_GPIO_Nokia6100.hh"

#include <iostream>

Beagle_GPIO	gpio;

int main()
{
	GPIO_PRINT( "==============================" );
	GPIO_PRINT( "BeagleBone GPIO Nokia6100 Test" );
	GPIO_PRINT( "==============================" );

	Beagle_GPIO_Nokia6100 lcd(
			&gpio,
			Beagle_GPIO::P8_46,	// BL
			Beagle_GPIO::P8_45,	// CS
			Beagle_GPIO::P8_44,	// SCLK
			Beagle_GPIO::P8_43,	// SDATA
			Beagle_GPIO::P8_42);	// RESET

	gpio.writePin( Beagle_GPIO::P8_46, 1 );
	// Init LCD screen
	lcd.initScreen();

	// Clear Screen
	//lcd.clearScreen();

	// Write a pixel
	for (int i=0;i<20;++i)
		lcd.setPixel( i,i, 0xFF, 0xFF, 0x00 );

	while(1)
	{
		gpio.writePin( Beagle_GPIO::P8_46, 0 );
		sleep(1);
		gpio.writePin( Beagle_GPIO::P8_46, 1 );
		sleep(1);
	}

	// Write a string to screen
	//lcd.goToPosition(3,0);
	//lcd.write( "Beagle_GPIO" );

	//lcd.goToPosition(3,1);
	//lcd.write( "Nokia6100 Test" );

	//lcd.clearScreen();

	return 0;
}
