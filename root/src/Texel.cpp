#include "Texel.h"

bool Texel::TextInit()
{
	if (!_fileFailure)
	{
		// Read the 18 byte TGA header
		if ( !fread(_header, 18, 1, _file))
		{
			printf("Failed to read header.\n");
			return InitFailure();
		}

		// Not uncrompressed tga format
		if ( _header[2] != 2)
		{
			printf("Tga must be an uncompressed file format.\n");
			exit(0);
			return InitFailure();
		}

		// Not 24 bits
		if ( _header[16] != 24 )
		{
			printf("Tga must be 24 bits per pixel.\n");
			exit(0);
			return InitFailure();
		}

		// Read the image pixels

		_width = ( _header[13] << 8 ) | _header[12];
		_height = ( _header[15] << 8 ) | _header[14];

		_buffer.resize( _width * _height * 3, 0 );

		if ( !fread( &_buffer[0], _buffer.size(), 1, _file ) )
		{
			printf( "Failed to read image pixel data.\n" );
			return InitFailure();
		}

		fclose( _file );

		return true;
	}
		printf("Unable to initialize, file failed to load.\n");
		return InitFailure();
}

void Texel::SetTex(Pixel & pix, float u, float v)
{
	if (v >= 1.0f)
	{
		v = .99f;
	}

	if ( u >= 1.0f)
	{
		u = .99f;
	}

	if ( v < 0.000001 )
	{
		v = 0;
	}

	if ( u < 0.000001 )
	{
		u = 0;
	}


	int wFac = u * _width;
	int hFac = v * _height;

	int index = wFac + (hFac * _width);

	pix.b = _buffer[index*3+0] * _pixelConverter;
	pix.g = _buffer[index*3+1] * _pixelConverter;
	pix.r = _buffer[index*3+2] * _pixelConverter;
}