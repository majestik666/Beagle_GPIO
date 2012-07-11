
#include "Beagle_GPIO.hh"
#include "Beagle_GPIO_Nokia6100.hh"

#include <iostream>

Beagle_GPIO	gpio;

int main()
{
	GPIO_PRINT( "==============================" );
	GPIO_PRINT( "BeagleBone GPIO Nokia6100 Test" );
	GPIO_PRINT( "==============================" );

#if 0
	// Regular pins interface
	Beagle_GPIO_Nokia6100 lcd(
			&gpio,
			Beagle_GPIO::P8_45,	// CS
			Beagle_GPIO::P8_44,	// SCLK
			Beagle_GPIO::P8_43,	// SDATA
			Beagle_GPIO::P8_42);	// RESET

	gpio.writePin( Beagle_GPIO::P8_46, 1 );
	// Init LCD screen
	lcd.initScreen();

	// Clear Screen
	//lcd.clearScreen();

	lcd.fillBox( 0, 0, 50, 50, 0xFF, 0x00, 0x00 );
	lcd.fillBox( 40, 40, 75, 75, 0x00, 0xFF, 0x00 );
	lcd.fillBox( 70, 70, 100, 100, 0x00, 0x00, 0xFF );

	lcd.print( 33, 25, "Beagle_GPIO", 0xFF, 0xFF, 0xFF );
	lcd.print( 35, 35, "Nokia 6100", 0xFF, 0xFF, 0xFF );
	lcd.print( 57, 45, "LCD", 0xFF, 0xFF, 0xFF );
#else
	// SPI Interface
	Beagle_GPIO_Nokia6100 lcd( & gpio, Beagle_GPIO::P8_42 );

	lcd.initScreen();

	for(int i=0;i<100;++i)
	{
		lcd.fillBox(0,0,132,132,0xFF,0,0);
		//lcd.fillBox(0,0,132,132,0,0xFF,0);
		//lcd.fillBox(0,0,132,132,0,0,0xFF);
		lcd.print( 33, i, "Beagle_GPIO", 0xFF, 0xFF, 0xFF );
	}
#endif
	sleep(1);

	return 0;
}
