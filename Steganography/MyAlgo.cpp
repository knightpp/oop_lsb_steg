#include "MyAlgo.h"

void MyAlgo::writeByte(byte byt3, std::vector<Pixel>::iterator& d) const
{
	d->setLSB(byt3 | 0xFE, (byt3 >> 1) | 0xFE, (byt3 >> 2) | 0xFE);			d += 1;
	d->setLSB((byt3 >> 3) | 0xFE, (byt3 >> 4) | 0xFE, (byt3 >> 5) | 0xFE);  d += 1;
	d->setLSB((byt3 >> 6) | 0xFE, (byt3 >> 7) | 0xFE, 0x0);					d += 1;
}

byte MyAlgo::readByte(std::vector<Pixel>::iterator& d) const
{
	/////////////////////////////////////////////////////////////
	byte a = d->getLSB().to_ulong(); d += 1;
	byte b = d->getLSB().to_ulong(); d += 1;
	byte c = d->getLSB().to_ulong(); d += 1;
	return (c << 6) + (b << 3) + a;
}

int MyAlgo::pack(SharedPixelsData pd, const std::vector<byte>& data)
{
	if (data.size() * sizeof(byte) > Pixel::bits * pd->getSize()) {
		return -1;
	}

	auto it = pd->getData().begin();
	writeByte((byte)data.size(), it);
	writeByte((byte)(data.size() >> 8), it);
	for(byte b : data)
	{
		writeByte(b, it);
	}
	return 0;
}

std::vector<byte> MyAlgo::unpack(SharedPixelsData pd)
{
	std::vector<byte> output;
	auto it = pd->getData().begin();
	byte low = readByte(it);
	byte hi	 = readByte(it);
	unsigned short int length = (hi << 8) + low;
	output.reserve(length);
	for (int i = 0; i < length; i++) {
		output.push_back(readByte(it));
	}
	return std::move(output);
}
