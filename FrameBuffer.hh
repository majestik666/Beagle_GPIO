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
 
#ifndef frame_buffer_hh
#define frame_buffer_hh
 
//=======================================================
//=======================================================

#include "Beagle_GPIO.hh"

//=======================================================
//=======================================================

class FrameBuffer
{
public:
	// Regular pins
	FrameBuffer( int _width, int _height );
	~FrameBuffer();

	// Clear Screen
	void clear();

	// Write a string to screen
	void print( unsigned char _x,
		    unsigned char _y,
		    const char * _string,
		    unsigned char _r,
		    unsigned char _g,
		    unsigned char _b );

	// Write a single pixel
	void setPixel( unsigned char _x, unsigned char _y, unsigned char _r, unsigned char _g, unsigned char _b );

	// Fill a box on screen
	void fillBox( unsigned char _x1, unsigned char _y1, unsigned char _x2, unsigned char _y2, unsigned char _c, unsigned char _g, unsigned char _b );

	// Draw line
	void drawLine( unsigned char _x0, unsigned char _y0, unsigned char _x1, unsigned char _y1, unsigned char _r, unsigned char _g, unsigned char _b );

	// Draw Polygon
	void drawPolygon( unsigned char _x0, unsigned char _y0,
			  unsigned char _x1, unsigned char _y1,
			  unsigned char _x2, unsigned char _y2,
			  unsigned char _x3, unsigned char _y3,
			  unsigned char _r, unsigned char _g, unsigned char _b );

	// Raster a line
	void rasterLine( int x0, int y0, int x1, int y1, int *rl );

	// Return the address of buffer
	unsigned char *getBuffer()
	{
		return m_buffer;
	}

private:
	// Write a single character
	void printChar( unsigned char _x, 
			unsigned char _y, 
			char _c, 
			unsigned char _r,
			unsigned char _g,
			unsigned char _b );

private:
	unsigned char *		m_buffer;
	int 			m_width;
	int			m_height;
	static const unsigned char 	font_5x8[];
};

//=======================================================
//=======================================================

#endif

//=======================================================
//=======================================================
