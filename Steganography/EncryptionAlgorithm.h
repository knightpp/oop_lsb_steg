#pragma once
#include "PixelsData.h"
#include "ImageFile.h"

class EncryptionAlgorithm {
public:
	virtual int pack(SharedPixelsData pd, const std::vector<byte>& data) = 0;
	virtual std::vector<byte> unpack(SharedPixelsData pd) = 0;
};