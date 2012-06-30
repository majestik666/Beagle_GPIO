
#include "Beagle_GPIO.hh"

#include <iostream>

Beagle_GPIO	gpio;

int main()
{
	GPIO_PRINT( "====================" );
	GPIO_PRINT( "BeagleBone GPIO Test" );
	GPIO_PRINT( "====================" );

	GPIO_PRINT( "Configuring Pin P8_46 as Output" );
	gpio.configurePin( Beagle_GPIO::P8_46, Beagle_GPIO::kOUTPUT );
	gpio.enablePinInterrupts( Beagle_GPIO::P8_46, false );

	for ( int i=0; i<5; ++i )
	{
		GPIO_PRINT( "Writing 1" );
		gpio.writePin( Beagle_GPIO::P8_46, 1 );
		GPIO_PRINT( "Waiting 500ms" );
		usleep(500000);
		GPIO_PRINT( "Writing 0" );
		gpio.writePin( Beagle_GPIO::P8_46, 0 );
		GPIO_PRINT( "Waiting 500ms" );
		usleep(500000);
	}
	return 0;
}
