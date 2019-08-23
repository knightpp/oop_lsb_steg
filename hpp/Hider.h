#pragma once
#include "EncryptionAlgorithm.h"
#include "ImageFile.h"

class Hider
{
private:
	EncryptionAlgorithm* ea;
public:
	Hider(EncryptionAlgorithm* ea);
	int pack(ImageFile* ir, const std::vector<byte>* data);
	std::vector<byte> unpack(ImageFile* ir);
};

