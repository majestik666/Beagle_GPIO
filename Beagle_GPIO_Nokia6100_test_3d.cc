
#include "Beagle_GPIO.hh"
#include "Beagle_GPIO_Nokia6100.hh"

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>

Beagle_GPIO	gpio;

#define abs(a)	(a>0?(a):-(a))

const float cube[24] = {
	-1.0, -1.0, -1.0,
	 1.0, -1.0, -1.0,
	 1.0,  1.0, -1.0,
	-1.0,  1.0, -1.0,
	-1.0, -1.0,  1.0,
	 1.0, -1.0,  1.0,
	 1.0,  1.0,  1.0,
	-1.0,  1.0,  1.0 };

const int edges[24] = {
	0, 1,
	1, 2,
	2, 3,
	3, 0,
	4, 5,
	5, 6,
	6, 7,
	7, 4,
	0, 4,
	1, 5,
	2, 6,
	3, 7 };

float rotation[3] = { 0.0, 0.0, 0.0 };
float rot_speed[3] = { 0.04, -0.08, 0.033 };

unsigned char * frame_buffer;

#define WIDTH	130
#define HEIGHT  130

void setPixel( int x, int y, unsigned char r, unsigned char g, unsigned char b )
{
	if (x>=0 && x<WIDTH && y>=0 && y<HEIGHT)
	{
		frame_buffer[3*(y*WIDTH+x)+0] = r;
		frame_buffer[3*(y*WIDTH+x)+1] = g;
		frame_buffer[3*(y*WIDTH+x)+2] = b;
	}
}

void drawLine( int x0, int y0, int x1, int y1, unsigned char r, unsigned char g, unsigned char b)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx,sy;
	if (x0<x1) sx=1; else sx=-1;
	if (y0<y1) sy=1; else sy=-1;
	int err = dx-dy;

	for(;;)
	{
		setPixel(x0,y0,r,g,b);
		setPixel(x0+1,y0,r,g,b);
		setPixel(x0-1,y0,r,g,b);
		if (x0==x1 && y0==y1)
			return;
		int err2 = 2*err;
		if (err2 > -dy)
		{
			err = err - dy;
			x0 = x0 + sx;
		}
		if (err2 < dx)
		{
			err = err + dx;
			y0 = y0 + sy;
		}
	}
}

void hsv2rgb(float h,float s,float v, float &r, float &g, float &b)
{
	if (s<0.001)
	{
		r = v;
		g = v;
		b = v;
	}
	else
	{
		if (h>1.0)
		{
			h = 0.0;
		}
		else
		{
			h *= 6.0;
		}

		int i = (int)(h);
		float f = h - i;

		float m = v * (1.0-s);
		float n = v * (1.0-s*f);
		float k = v * (1.0-s*(1.0-f));

		if (i==0) { r=v; g=k; b=m; return; }
		if (i==1) { r=n; g=v; b=m; return; }
		if (i==2) { r=m; g=v; b=k; return; }
		if (i==3) { r=m; g=n; b=v; return; }
		if (i==4) { r=k; g=m; b=v; return; }
		if (i==5) { r=v; g=m; b=n; return; }
	}
}

int main()
{
	GPIO_PRINT( "=================================" );
	GPIO_PRINT( "BeagleBone GPIO Nokia6100 Test 3D" );
	GPIO_PRINT( "=================================" );

	frame_buffer = new unsigned char[WIDTH*HEIGHT*3];

	// SPI Interface
	Beagle_GPIO_Nokia6100 lcd( & gpio, Beagle_GPIO::P8_42 );

	lcd.initScreen();

	float new_pts[24];

	int pts[16];

	float camx = 0.0;
	float camy = 0.0;
	float camz = 2.0;

	for(int i=0;i<1000;++i)
	{
		// Clear the buffer
		memset( frame_buffer, 0, WIDTH*HEIGHT*3 );

		// Checkerboard background
		int xo = 0;//25.0*sin(3*i/100.0)*cos(2*i/100.0);
		int yo = 0;//25.0*sin(1*i/100.0)*cos(4*i/100.0);

		for (int x=0;x<WIDTH;x++)
		{
			int xx = ((50+x+xo)%WIDTH) % 32;
			for (int y=0;y<HEIGHT;++y)
			{
				int yy = ((50+y+yo)%HEIGHT) % 32;
				if ((xx<16 && yy<16) || (xx>16 && yy>16))
					setPixel(x,y,0xFF,0xFF,0xFF);
			}
		}

		float cosT = cos(rotation[0]);
		float sinT = sin(rotation[0]);
		float cosP = cos(rotation[1]);
		float sinP = sin(rotation[1]);
		float cosTcosP = cosT*cosP;
		float cosTsinP = cosT*sinP;
		float sinTcosP = sinT*cosP;
		float sinTsinP = sinT*sinP;

		int scaleFactor = WIDTH/4;
		float near = 3;
		float nearToObj = 1.5 + 2.5*sin(5*i/100.0);
		float x0,y0,z0,x1,y1,z1;

		for (int j=0;j<8;++j)
		{
			x0 = cube[3*j+0];
			y0 = cube[3*j+1];
			z0 = cube[3*j+2];

			x1 = cosT*x0 + sinT*z0;
			y1 = -sinTsinP*x0 + cosP*y0 + cosTsinP*z0;
			z1 = camz + cosTcosP*z0 - sinTcosP*x0 - sinP*y0;

			float fac = near * 1.0f / (z1+near+nearToObj);

			pts[2*j+0] = (int)(WIDTH/2.0f + scaleFactor*fac*x1 + 0.5 );
			pts[2*j+1] = (int)(WIDTH/2.0f + scaleFactor*fac*y1 + 0.5 );
		}

		for (int j=0;j<12;++j)
		{
			int p1 = edges[2*j+0];
			int p2 = edges[2*j+1];

			drawLine( pts[2*p1+0],pts[2*p1+1], pts[2*p2+0],pts[2*p2+1], 0xFF,0,0 );
		}

		// Send Frame Buffer to screen
		lcd.writeBuffer( frame_buffer, 0,0, WIDTH,HEIGHT );

		for (int j=0;j<3;++j)
			rotation[j] += rot_speed[j];
	}

	delete [] frame_buffer;

	return 0;
}
