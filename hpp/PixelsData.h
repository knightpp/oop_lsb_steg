#pragma once
#include <vector>
#include "Pixel.h"


class PixelsData {
    friend class PixelBitIterator;
private:
	std::vector<Pixel>* pixels;
//	size_t size;

public:
	PixelsData()
	{
        pixels = new std::vector<Pixel>();
	}
/*	PixelsData(const PixelsData& other)
	{
        pixels = new std::vector<Pixel>(*other.pixels);
	}*/
	PixelsData(PixelsData&& other) noexcept
	{
		this->pixels = other.pixels;
		other.pixels = nullptr;
	}
	PixelsData(size_t size)
	{
        pixels = new std::vector<Pixel>();
		pixels->reserve(size);
	}

	~PixelsData()
	{
		delete pixels;
	}

	void append(byte r, byte g, byte b) {
		pixels->emplace_back(r, g, b);
	}

	std::vector<Pixel>& getData(){
		return *pixels;
	}

	size_t getSize() const {
		return pixels->size();
	}

};