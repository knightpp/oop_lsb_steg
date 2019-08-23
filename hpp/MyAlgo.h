#pragma once
#include "EncryptionAlgorithm.h"
#include "PixelsData.h"
#include "Pixel.h"
#include "ImageFile.h"
#include <vector>
#include <bitset>
#include "PixelBitIterator.h"

class MyAlgo :
	public EncryptionAlgorithm
{
private:
	void writeByte(byte byt3, PixelBitIterator& d) const;
	byte readByte(PixelBitIterator& d) const;
public:
	// Inherited via EncryptionAlgorithm
	int pack(SharedPixelsData pd, const std::vector<byte>& data) override;
	std::vector<byte> unpack(SharedPixelsData pd) override;
};

