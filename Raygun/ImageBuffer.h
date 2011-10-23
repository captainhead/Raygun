#pragma once

#ifndef IMAGE_BUFER
#define IMAGE_BUFER

#include "Colour.h"
#include "TRACE.h"

////////////////////////////////////////////////////////////////////////////////
// class ImageBuffer
//
// Contains an image generated by RayTracer object
////////////////////////////////////////////////////////////////////////////////
class ImageBuffer
{
public:
	ImageBuffer(int inw, int inh)
	{
		_width = inw;
		_height = inh;
		
		buffer = new float[_width*_height*3];
	}
	~ImageBuffer(void)
	{
		delete [] buffer;
	}

	// Retrieve width and height
	inline int width() const { return _width; }
	inline int height() const { return _height; }







	// Get and set pixels as Colour objects
	// -NOTE row is inverted (rendered image is upside down), so getPixel() flips it over
	inline Colour getPixel(int row, int col) const
	{
		int i = (((_height-1)-row)*_width + col) * 3;
		return Colour(buffer[i], buffer[i+1], buffer[i+2]);
	}
	inline void setPixel(int row, int col, Colour c)
	{
		int i = (row*_width + col) * 3;
		buffer[i] = c.r();
		buffer[i+1] = c.g();
		buffer[i+2] = c.b();
	}





	// Directly set the image buffer to the supplied float array. rgbArray must be dynamically allocated
	inline void setBuffer(float *rgbArray) { buffer = rgbArray; }
	// Get a reference to the image buffer array. Note, modifying the returned array will permanently modify the image buffer contents
	inline float *getBuffer() { return buffer; }
	




	// This returns 32bit colour values stored in char array (mainly used for win32 conversion to BITMAP)
	char *getCharArray()
	{
		char *charBuffer = new char[_width*_height*4];

		for(int row=0; row<_height; row++) for(int col=0; col<_width; col++)
		{
			int iBuf = (row*_width + col)*3;
			int iOut = ((_height-1-row)*_width + col)*4;

			charBuffer[iOut] = static_cast<int>(buffer[iBuf+2]*255);
			charBuffer[iOut+1] = static_cast<int>(buffer[iBuf+1]*255);
			charBuffer[iOut+2] = static_cast<int>(buffer[iBuf]*255);
			charBuffer[iOut+3] = static_cast<int>(255);
		}

		return charBuffer;
	}



	/*
	// Flip the image buffer array vertically (upside down)
	void flipV()
	{
		TRACE("%d %d\n", _width, _height);
		// There are 3 "columns", one for each component
		float temp;
		for(int row=0; row<_height/2; row++) for(int col=0; col<_width; col++)
		{
			int i = (row*_width + col)*3;
			int invi = ((_height-row-1)*_width + col)*3;
			
			temp = buffer[i];
			buffer[i] = buffer[invi];
			buffer[invi] = temp;
			
			temp = buffer[i+1];
			buffer[i+1] = buffer[invi+1];
			buffer[invi+1] = temp;
			
			temp = buffer[i+2];
			buffer[i+2] = buffer[invi+2];
			buffer[invi+2] = temp;
		}
	}
	*/





	// Generate rainbow static
	void rainbowStatic()
	{
		for(int row=0; row<_height; row++) for(int col=0; col<_width; col++)
		{
			Colour out(	(float)rand()/(float)RAND_MAX,
						(float)rand()/(float)RAND_MAX,
						(float)rand()/(float)RAND_MAX);
			setPixel(row, col, out);
		}
	}

	// Generate gradient
	void gradient()
	{
		for(int row=0; row<_height; row++) for(int col=0; col<_width; col++)
		{
			Colour out(	((float)row/(float)_height)*1.0f,
						0.0f,
						((float)col/(float)_width)*1.0f);
			setPixel(row, col, out);
		}
	}

private:
	float* buffer;

	int _width;
	int _height;
};

#endif