#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <iterator>
#include <cstring>
#include <cassert>
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
	void readFile() override;
	void saveFile() override;
	SharedPixelsData getArray() override;

};

