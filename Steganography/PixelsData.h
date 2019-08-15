#pragma once
#include <vector>
#include "Pixel.h"

class PixelsData {
private:
	std::vector<Pixel>* data;
public:
	PixelsData()
	{
		data = new std::vector<Pixel>();
	}
	PixelsData(const PixelsData& other)
	{
		data = new std::vector<Pixel>(*other.data);
	}
	PixelsData(PixelsData&& other) noexcept
	{
		this->data = other.data;
		other.data = nullptr;
	}
	PixelsData(size_t size)
	{
		data = new std::vector<Pixel>(size);
	}

	~PixelsData()
	{
		delete data;
	}

	void append(byte r, byte g, byte b) {
		data->emplace_back(r,g,b);
	}

	std::vector<Pixel>& getData(){
		return *data;
	}

	size_t getSize() const {
		return data->size();
	}
};