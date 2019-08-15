#pragma once
#include "EncryptionAlgorithm.h"
#include "PixelsData.h"
#include "Pixel.h"
#include "ImageFile.h"
#include <vector>
#include <bitset>


class MyAlgo :
	public EncryptionAlgorithm
{
private:
	void writeByte(byte byt3, std::vector<Pixel>::iterator& d) const;
	byte readByte(std::vector<Pixel>::iterator& d) const;
public:
	// Inherited via EncryptionAlgorithm
	virtual int pack(SharedPixelsData pd, const std::vector<byte>& data) override;
	virtual std::vector<byte> unpack(SharedPixelsData pd) override;
};

