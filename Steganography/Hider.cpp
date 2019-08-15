#include "Hider.h"

Hider::Hider(EncryptionAlgorithm* ea)
{
	this->ea = ea;
}

int Hider::pack(ImageFile* ir,const std::vector<byte>* data)
{
	ea->pack(ir->getArray(), *data);
	return 0;
}

std::vector<byte> Hider::unpack(ImageFile* ir)
{
	return std::move(ea->unpack(ir->getArray()));
}
