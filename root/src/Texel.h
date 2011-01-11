#pragma once
#include "PixelToaster.h"
using namespace PixelToaster;
class Texel
{
	vector<unsigned char> _buffer;
	unsigned char _header[18];
	FILE * _file;
	bool _fileFailure;
	float _pixelConverter;
	int _width;
	int _height;
public:
	Texel(void){};
	~Texel(void){};

	Texel(const char fileName[]) 
	{	
		_file = fopen(fileName, "rb");
		if (!_file)
		{
			printf("Failed to load file.\n");
			_fileFailure = true;
		}
		_fileFailure = false;
		_pixelConverter = 1.0f/255.0f;
	}

	bool InitFailure()
	{
		_width = 0;
		_height = 0;
		return false;
	}

	bool TextInit();

	void SetTex(Pixel & pix, float u, float v);
};

