
#include "Beagle_GPIO.hh"
#include "Beagle_GPIO_Nokia6100.hh"

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>

Beagle_GPIO	gpio;

#define abs(a)	(a>0?(a):-(a))

// Vertices
const int nbPts = 8;
const float cube[nbPts*3] = {
	-1.0, -1.0, -1.0,	// 0
	 1.0, -1.0, -1.0,	// 1
	 1.0,  1.0, -1.0,	// 2
	-1.0,  1.0, -1.0,	// 3
	-1.0, -1.0,  1.0,	// 4
	 1.0, -1.0,  1.0,	// 5
	 1.0,  1.0,  1.0,	// 6
	-1.0,  1.0,  1.0 };	// 7

// Edges
const int nbEdges = 12;
const int edges[nbEdges*2] = {
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

// Faces
const int nbFaces = 6;
const int faces[nbFaces*4] = {
	0, 1, 2, 3,	// Front
	4, 5, 6, 7,	// Back
	0, 1, 5, 4,	// Bottom
	3, 2, 6, 7,	// Top
	1, 5, 6, 2,	// Right
	0, 4, 7, 3};	// Left

// Faces colors
const unsigned char faces_color[nbFaces*3] = {
	0xFF, 0x00, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0x00, 0xFF,
	0xFF, 0xFF, 0x00,
	0xFF, 0x00, 0xFF,
	0x00, 0xFF, 0xFF };

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

void rasterLine( int x0, int y0, int x1, int y1, int *rl )
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx,sy;
	if (x0<x1) sx=1; else sx=-1;
	if (y0<y1) sy=1; else sy=-1;
	int err = dx-dy;

	for(;;)
	{
		if (y0>=0 && y0<130)
		{
			if (x0 < rl[2*y0+0])	rl[2*y0+0] = x0>=0?x0:0;
			if (x0 > rl[2*y0+1])	rl[2*y0+1] = x0<130?x0:130;
		}

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

void drawPolygons( float *tp, int *pp )
{
	float d[nbFaces];
	// First calculate mid z position of faces
	for (int i=0;i<nbFaces;++i)
	{
		d[i] = 0.0;
		for (int j=0;j<4;++j)
			d[i] += tp[3*faces[4*i+j]+2];
	}

	// Sort the faces
	int sp[nbFaces] = { 0,1,2,3,4,5 };
	for (int i=0;i<nbFaces-1;++i)
	{
		for (int j=i;j<nbFaces;++j)
		{
			if (d[i]<d[j])
			{
				float t = d[j]; d[j] = d[i]; d[i] = t;
				int tt = sp[j]; sp[j] = sp[i]; sp[i] = tt;
			}
		}
	}

	// Draw back to front
	for (int p=0;p<nbFaces;++p)
	{
		// Sorted Face Index 
		int pi = sp[p];
		
		int rl[130*2];
		for (int i=0;i<130;++i)
		{
			rl[2*i+0] = 131;
			rl[2*i+1] = -1;
		}

		// Fill in the 3 edges
		for (int i=0;i<4;++i)
		{
			int p0 = faces[4*pi+0];
			int p1 = faces[4*pi+1];
			int p2 = faces[4*pi+2];
			int p3 = faces[4*pi+3];
			rasterLine( pp[2*p0+0], pp[2*p0+1], pp[2*p1+0], pp[2*p1+1], rl );
			rasterLine( pp[2*p1+0], pp[2*p1+1], pp[2*p2+0], pp[2*p2+1], rl );
			rasterLine( pp[2*p2+0], pp[2*p2+1], pp[2*p3+0], pp[2*p3+1], rl );
			rasterLine( pp[2*p3+0], pp[2*p3+1], pp[2*p0+0], pp[2*p0+1], rl );
		}

		for (int i=0;i<130;++i)
		{
			if ( rl[2*i+1] > rl[2*i+0] )
			{
				for( int j=rl[2*i+0]; j<=rl[2*i+1]; ++j )
					setPixel( j, i, faces_color[3*pi+0], faces_color[3*pi+1], faces_color[3*pi+2] );
			}
		}
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

	float tp[24];

	int pp[16];

	float camx = 0.0;
	float camy = 0.0;
	float camz = 2.0;

	for(int i=0;i<1000;++i)
	{
		// Clear the buffer
		memset( frame_buffer, 0, WIDTH*HEIGHT*3 );

		// Checkerboard background
		int xo = 25.0*sin(10*i/100.0)*cos(6*i/100.0);
		int yo = 25.0*sin(5*i/100.0)*cos(7.5*i/100.0);

		for (int x=0;x<WIDTH;x++)
		{
			int xx = (50+x+xo)% 32;
			for (int y=0;y<HEIGHT;++y)
			{
				int yy = (50+y+yo)% 32;
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
		float nearToObj = 1.5 + 4.5*sin(5*i/100.0);
		float x0,y0,z0;
		float fac;

		for (int j=0;j<nbPts;++j)
		{
			x0 = cube[3*j+0];
			y0 = cube[3*j+1];
			z0 = cube[3*j+2];

			tp[3*j+0] = cosT*x0 + sinT*z0;
			tp[3*j+1] = -sinTsinP*x0 + cosP*y0 + cosTsinP*z0;
			tp[3*j+2] = camz + cosTcosP*z0 - sinTcosP*x0 - sinP*y0;

			fac = scaleFactor * near * 1.0f / (tp[3*j+2]+near+nearToObj);

			pp[2*j+0] = (int)(WIDTH/2.0f + fac*tp[3*j+0] + 0.5 );
			pp[2*j+1] = (int)(WIDTH/2.0f + fac*tp[3*j+1] + 0.5 );
		}

		/*
		for (int j=0;j<nbEdges;++j)
		{
			int p1 = edges[2*j+0];
			int p2 = edges[2*j+1];

			drawLine( pp[2*p1+0],pp[2*p1+1], pp[2*p2+0],pp[2*p2+1], 0xFF,0,0 );
		}
		*/

		drawPolygons( tp, pp );

		// Send Frame Buffer to screen
		lcd.writeBuffer( frame_buffer, 0,0, WIDTH,HEIGHT );

		for (int j=0;j<3;++j)
			rotation[j] += rot_speed[j];
	}

	delete [] frame_buffer;

	return 0;
}
