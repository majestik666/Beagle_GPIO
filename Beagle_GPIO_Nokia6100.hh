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
 
#ifndef beagle_gpio_Nokia6100_hh
#define beagle_gpio_Nokia6100_hh
 
//=======================================================
//=======================================================

#include "Beagle_GPIO.hh"

//=======================================================
//=======================================================

class Beagle_GPIO_Nokia6100
{
public:
	Beagle_GPIO_Nokia6100(
			Beagle_GPIO * gpio,
			unsigned short _pin_BL,
			unsigned short _pin_CS,
			unsigned short _pin_SCLK,
			unsigned short _pin_SDATA,
			unsigned short _pin_RESET );

	~Beagle_GPIO_Nokia6100();

	// Initialize Screen
	void initScreen();

	// Clear Screen
	void clearScreen();

	// Write a string to screen
	void write( unsigned char _x,
		    unsigned char _y,
		    const char * _string,
		    unsigned char _r,
		    unsigned char _g,
		    unsigned char _b );

	// Write a single pixel
	void setPixel( unsigned char _x, unsigned char _y, unsigned char _r, unsigned char _g, unsigned char _b );

	// Fill a box on screen
	void fillBox( unsigned char _x1, unsigned char _y1, unsigned char _x2, unsigned char _y2, unsigned char _c, unsigned char _g, unsigned char _b );

private:
	// Shift a byte to the screen
	void shiftBits( unsigned char _c );

	// Send a command to the screen
	void sendCommand( unsigned char _cmd );

	// Send data to the screen
	void sendData( unsigned char _data );

	// Set window on display
	void setWindow( unsigned char _x1, unsigned char _y1, unsigned char _x2, unsigned char _y2 );

	// Write a single character
	void writeChar( unsigned char _x, 
			unsigned char _y, 
			char _c, 
			unsigned char _r,
			unsigned char _g,
			unsigned char _b );

	// Write a pair of pixels at a time
	void writePair( unsigned char _r1,
			unsigned char _g1,
			unsigned char _b1,
			unsigned char _r2,
			unsigned char _g2,
			unsigned char _b2 );

private:
	Beagle_GPIO * 	m_gpio;
	unsigned short 	m_pin_BL;
	unsigned short 	m_pin_CS;
	unsigned short 	m_pin_SCLK;
	unsigned short 	m_pin_SDATA;
	unsigned short 	m_pin_RESET;

	// Array storing the font
	static const unsigned char font_5x8[];

public:
	enum
	{
		// Epson S1D15G10 Command Set 
		kSWRESET    = 0x01,
		kCASET      = 0x15,
		kPWRCTR     = 0x20,
		kNOP	    = 0x25,
		kRAMWR      = 0x5c,
		kRAMRD      = 0x5d,
		kPASET      = 0x75,
		kEPSRRD1    = 0x7c,
		kEPSRRD2    = 0x7d,
		kVOLCTR     = 0x81,
		kTMPGRD     = 0x82,
		kSLPOUT     = 0x94,
		kSLPIN      = 0x95,
		kDISNOR     = 0xa6,
		kDISINV     = 0xa7,
		kPTLIN      = 0xa8,
		kPTLOUT     = 0xa9,
		kASCSET     = 0xaa,
		kSCSTART    = 0xab,
		kDISOFF     = 0xae,
		kDISON      = 0xaf,
		kCOMSCN     = 0xbb,
		kDATCTL     = 0xbc,
		kDISCTL     = 0xca,
		kEPCOUT     = 0xcc,
		kRGBSET8    = 0xce,
		kEPCTIN     = 0xcd,
		kOSCON      = 0xd1,
		kOSCOFF     = 0xd2,
		kVOLUP      = 0xd6,
		kVOLDOWN    = 0xd7,
		kRMWIN      = 0xe0,
		kRMWOUT     = 0xee,
		kEPMWR      = 0xfc,
		kEPMRD      = 0xfd
	} Commands;
};

//=======================================================
//=======================================================

#endif

//=======================================================
//=======================================================
