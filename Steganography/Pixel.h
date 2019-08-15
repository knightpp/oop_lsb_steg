#pragma once
#include <bitset>

typedef unsigned char byte;

class Pixel {
	byte r, g, b;
public:
	const static size_t bits = 3;
public:
	Pixel() = default;
	Pixel(byte r, byte g, byte b) : r(r), g(g), b(b)
	{
	}

	void setRGB(byte r, byte g, byte b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}

	// byte = [0 0 0 0 0 0 0 1/0]
	void setLSB(byte _r, byte _g, byte _b) {
		r = (r & ~1UL) | (_r & 1UL);
		g = (g & ~1UL) | (_g & 1UL);
		b = (b & ~1UL) | (_b & 1UL);
	}

	std::bitset<bits> getLSB() const {
		std::bitset<bits> bitset;
		bitset[0] = r & 0x1;
		bitset[1] = g & 0x1;
		bitset[2] = b & 0x1;
		return bitset;
	}

	void writeRGB(byte& _r, byte& _g, byte& _b) {
		_r = r;
		_g = g;
		_b = b;
	}
};