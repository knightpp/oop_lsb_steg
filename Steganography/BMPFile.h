#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <iterator>
#include "ImageFile.h"

class BMPFile :
	public ImageFile
{
private:
	int width, height;
public:
	BMPFile(const std::string& file);
	BMPFile(std::string&& file) ;
	// Inherited via ImageFile
	virtual void readFile() override;
	virtual void saveFile() override;
	virtual SharedPixelsData getArray() override;

};

