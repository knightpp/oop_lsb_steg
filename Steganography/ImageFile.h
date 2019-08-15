#pragma once
#include <string>
#include <memory>
#include "PixelsData.h"

typedef std::shared_ptr<PixelsData> SharedPixelsData;
class ImageFile {
public:
	ImageFile(const std::string& path) {
		this->path = path;
		pd = std::make_shared<PixelsData>();
	};
	ImageFile(std::string&& path)
	{
		this->path = std::move(path);
		pd = std::make_shared<PixelsData>();
	}
	virtual void readFile() = 0;
	virtual void saveFile() = 0;
	virtual SharedPixelsData getArray() = 0;

public:
	std::string path;
	SharedPixelsData pd;
};