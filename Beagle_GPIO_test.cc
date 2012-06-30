
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

	return 0;
}

