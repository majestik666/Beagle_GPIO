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

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

//=======================================================
//=======================================================
 
#include "Beagle_GPIO.hh"

//=======================================================
//=======================================================

const int Beagle_GPIO::GPIO_Pin_Bank[] = 
{
	-1, -1,  1,  1,  1,	// P8_1  -> P8_5
	 1, -1, -1, -1, -1,	// P8_6  -> P8_10
	 1,  1, -1,  0,  1, 	// P8_11 -> P8_15
	 1,  0,  2, -1,  1, 	// P8_16 -> P8_20
	 1,  1,  1,  1,  1, 	// P8_21 -> P8_25
	 1,  2,  2,  2,  2, 	// P8_26 -> P8_30
	-1, -1, -1, -1, -1, 	// P8_31 -> P9_35
	-1, -1, -1,  2,  2, 	// P8_36 -> P8_40
	 2,  2,  2,  2,  2, 	// P8_41 -> P8_45
	 2,			// P8_46
	-1, -1, -1, -1, -1, 	// P9_1  -> P9_5
	-1, -1, -1, -1, -1, 	// P9_6  -> P9_10
	-1,  1, -1, -1,  1, 	// P9_11 -> P9_15
	-1, -1, -1, -1, -1,	// P9_16 -> P9_20
	-1, -1,  1, -1,  3, 	// P9_21 -> P9_25
	-1,  3, -1, -1, -1, 	// P9_26 -> P9_30
	-1, -1, -1, -1, -1, 	// P9_31 -> P9_35
	-1, -1, -1, -1, -1, 	// P9_36 -> P9_40
	-1,  0, -1, -1, -1, 	// P9_41 -> P9_45
	-1			// P9_46
};

//=======================================================
//=======================================================

const int Beagle_GPIO::GPIO_Pin_Id[] = 
{
	-1, -1,  6,  7,  2,	// P8_1  -> P8_5
	 3, -1, -1, -1, -1,	// P8_6  -> P8_10
	13, 12, -1, 26, 15, 	// P8_11 -> P8_15
	14, 27,  1, -1, 31, 	// P8_16 -> P8_20
	30,  5,  4,  1,  0, 	// P8_21 -> P8_25
	29, 22, 24, 23, 25, 	// P8_26 -> P8_30
	-1, -1, -1, -1, -1, 	// P8_31 -> P9_35
	-1, -1, -1, 12, 13, 	// P8_36 -> P8_40
	10, 11,  8,  9,  6, 	// P8_41 -> P8_45
	 7,			// P8_46
	-1, -1, -1, -1, -1, 	// P9_1  -> P9_5
	-1, -1, -1, -1, -1,	// P9_6  -> P9_10
	-1, 28, -1, -1, 16, 	// P9_11 -> P9_15
	-1, -1, -1, -1, -1, 	// P9_16 -> P9_20
	-1, -1, 17, -1, 21, 	// P9_21 -> P9_25
	-1, 19, -1, -1, -1, 	// P9_26 -> P9_30
	-1, -1, -1, -1, -1, 	// P9_31 -> P9_35
	-1, -1, -1, -1, -1, 	// P9_36 -> P9_40
	-1,  7, -1, -1, -1, 	// P9_41 -> P9_45
	-1			// P9_46
};

//=======================================================
//=======================================================

const unsigned long Beagle_GPIO::GPIO_Base[] = 
{
	0x44E07000,	// GPIO0
	0x4804C000,	// GPIO1
	0x481AC000,	// GPIO2
	0x481AE000	// GPIO3
};

//=======================================================
//=======================================================
 
Beagle_GPIO::Beagle_GPIO()
{
	GPIO_PRINT( "Beagle_GPIO::Beagle_GPIO()" );
	
	// Not initialized by default
	m_active = false;
	
	// Opening /dev/mem first
	GPIO_PRINT( "Opening /dev/mem" );
	m_gpio_fd = open( "/dev/mem", O_RDWR | O_SYNC );
	if ( m_gpio_fd < 0 )
	{
		GPIO_ERROR( "Cannot open /dev/mem" );
		return;
	}
	
	// Now mapping the GPIO registers
	for ( int i=0; i<4; ++i)
	{
		// Map a GPIO bank
		m_gpio[i] = (unsigned long *)mmap( NULL, 0xFFF, PROT_READ | PROT_WRITE, MAP_SHARED, m_gpio_fd, GPIO_Base[i] );
		if ( m_gpio[i] == MAP_FAILED )
		{
			GPIO_ERROR( "GPIO Mapping failed for GPIO Module " << i );
			return;
		}
	}
	
	// Init complete and successfull
	m_active = true;

	GPIO_PRINT( "Beagle GPIO Initialized" );
}
 
//=======================================================
//=======================================================
 
Beagle_GPIO::~Beagle_GPIO()
{
	GPIO_PRINT( "Beagle_GPIO::~Beagle_GPIO()" );
	if ( m_active && m_gpio_fd)
		close( m_gpio_fd );
}
 
//=======================================================
//=======================================================
 
// Configure pin as input/output
Beagle_GPIO::Beagle_GPIO_Status Beagle_GPIO::configurePin( unsigned short _pin, Beagle_GPIO_Direction _direction )
{
	if ( !m_active )
		return kFail;
	
	assert(GPIO_Pin_Bank[_pin]>=0);
	assert(GPIO_Pin_Id[_pin]>=0);
	
	unsigned long v = 0x1 << GPIO_Pin_Id[_pin];
	
	if ( _direction == kINPUT)
		m_gpio[GPIO_Pin_Bank[_pin]][kOE/4] |= v;
	else
		m_gpio[GPIO_Pin_Bank[_pin]][kOE/4] &= ~v;
	
}
 
//=======================================================
//=======================================================

// Write a value to a pin
Beagle_GPIO::Beagle_GPIO_Status Beagle_GPIO::writePin( unsigned short _pin, unsigned char _value )
{
	assert(GPIO_Pin_Bank[_pin]>=0);
	assert(GPIO_Pin_Id[_pin]>=0);

	unsigned long v = (_value & 0x01) << GPIO_Pin_Id[_pin];
	unsigned long mask = 0x1 << GPIO_Pin_Id[_pin];

	// Remove bit
	m_gpio[GPIO_Pin_Bank[_pin]][kDATAOUT] &= ~mask;
	// Assign new bit value
	m_gpio[GPIO_Pin_Bank[_pin]][kDATAOUT] |= v;
}
 
//=======================================================
//=======================================================

// Read a value from a pin
unsigned char Beagle_GPIO::readPin( unsigned short _pin, Beagle_GPIO::Beagle_GPIO_Status & status )
{
	assert(GPIO_Pin_Bank[_pin]>=0);
	assert(GPIO_Pin_Id[_pin]>=0);

	unsigned long bit = GPIO_Pin_Id[_pin];
	return (m_gpio[GPIO_Pin_Bank[_pin]][kDATAIN] & (0x1 << bit)) >> bit;
}
 
//=======================================================
//=======================================================

 
