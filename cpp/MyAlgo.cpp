#include "../hpp/MyAlgo.h"

void MyAlgo::writeByte(byte byt3, PixelBitIterator& d) const
{
    d.pushBit(byt3 >> 0);
    d.pushBit(byt3 >> 1);
    d.pushBit(byt3 >> 2);
    d.pushBit(byt3 >> 3);
    d.pushBit(byt3 >> 4);
    d.pushBit(byt3 >> 5);
    d.pushBit(byt3 >> 6);
    d.pushBit(byt3 >> 7);
}

byte MyAlgo::readByte(PixelBitIterator& d) const
{
	return d.getNextByte();
}

int MyAlgo::pack(SharedPixelsData pd, const std::vector<byte>& data)
{
	if (data.size() * sizeof(byte) > Pixel::bits * pd->getSize()) {
		return -1;
	}

	auto it = pd->getData().begin();
	PixelBitIterator pbi(pd);

   // PixelBitIterator pbi2(pd);
	writeByte((byte)data.size(), pbi);
	writeByte((byte)(data.size() >> 8), pbi);

	for(byte b : data)
	{
		writeByte(b, pbi);
	}
	return 0;
}

std::vector<byte> MyAlgo::unpack(SharedPixelsData pd)
{
	std::vector<byte> output;
	PixelBitIterator pbi(pd);
	byte low = readByte(pbi);
	byte hi	 = readByte(pbi);
	unsigned short int length = (hi << 8) + low;
	output.reserve(length);
	for (int i = 0; i < length; i++) {
		output.push_back(readByte(pbi));
	}
	return std::move(output);
}
