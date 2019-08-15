#include "BMPFile.h"



BMPFile::BMPFile(const std::string& file) : ImageFile(file), height(-1), width(-1)
{
}

BMPFile::BMPFile(std::string&& file) : ImageFile(file), height(-1), width(-1)
{
}

void BMPFile::readFile()
{
	int i;
	FILE* f;
	fopen_s(&f, path.c_str(), "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

	// extract image height and width from header
	int width, height;
	memcpy(&width, info + 18, sizeof(int));
	memcpy(&height, info + 22, sizeof(int));

	this->width = width;
	this->height = height;

	int heightSign = 1;
	if (height < 0) {
		heightSign = -1;
	}

	int size = 3 * width * abs(height);
	_ASSERT(size > 0);
	unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
	fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
	fclose(f);

	if (heightSign == 1) {
		for (i = 0; i < size; i += 3)
		{
			std::swap(data[i], data[i + 2]);
			pd->append(data[i], data[i + 1], data[i + 2]);
		}
	}
	delete[] data;
}

SharedPixelsData BMPFile::getArray()
{
	return pd;
}

void BMPFile::saveFile()
{
	unsigned int headers[13];
	FILE* outfile;
	int extrabytes;
	int paddedsize;
	int x; int y; int n;
	int red, green, blue;

	extrabytes = 4 - ((width * 3) % 4);                 // How many bytes of padding to add to each
														// horizontal line - the size of which must
														// be a multiple of 4 bytes.
	if (extrabytes == 4)
		extrabytes = 0;

	paddedsize = ((width * 3) + extrabytes) * height;

	// Headers...
	// Note that the "BM" identifier in bytes 0 and 1 is NOT included in these "headers".

	headers[0] = paddedsize + 54;      // bfSize (whole file size)
	headers[1] = 0;                    // bfReserved (both)
	headers[2] = 54;                   // bfOffbits
	headers[3] = 40;                   // biSize
	headers[4] = width;  // biWidth
	headers[5] = height; // biHeight

	// Would have biPlanes and biBitCount in position 6, but they're shorts.
	// It's easier to write them out separately (see below) than pretend
	// they're a single int, especially with endian issues...

	headers[7] = 0;                    // biCompression
	headers[8] = paddedsize;           // biSizeImage
	headers[9] = 0;                    // biXPelsPerMeter
	headers[10] = 0;                    // biYPelsPerMeter
	headers[11] = 0;                    // biClrUsed
	headers[12] = 0;                    // biClrImportant

	fopen_s(&outfile, path.c_str(), "wb");

	//
	// Headers begin...
	// When printing ints and shorts, we write out 1 character at a time to avoid endian issues.
	//

	fprintf(outfile, "BM");

	for (n = 0; n <= 5; n++)
	{
		fprintf(outfile, "%c", headers[n] & 0x000000FF);
		fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
		fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
		fprintf(outfile, "%c", (headers[n] & (unsigned int)0xFF000000) >> 24);
	}

	// These next 4 characters are for the biPlanes and biBitCount fields.

	fprintf(outfile, "%c", 1);
	fprintf(outfile, "%c", 0);
	fprintf(outfile, "%c", 24);
	fprintf(outfile, "%c", 0);

	for (n = 7; n <= 12; n++)
	{
		fprintf(outfile, "%c", headers[n] & 0x000000FF);
		fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
		fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
		fprintf(outfile, "%c", (headers[n] & (unsigned int)0xFF000000) >> 24);
	}

	//
	// Headers done, now write the data...
	//
	auto& data = pd->getData();
	auto it = data.begin();

	for (y = height - 1; y >= 0; y--)     // BMP image format is written from bottom to top...
	{
		for (x = 0; x <= width - 1; x++)
		{
			byte r, g, b;
			it->writeRGB(r, g, b);
			//std::cout << "Writing RGB [ " << (int)r << ", " << (int)g << ", " << (int)b << " ]\n";
			it += 1;

			fprintf(outfile, "%c", b);
			fprintf(outfile, "%c", g);
			fprintf(outfile, "%c", r);
		}
		if (extrabytes)      // See above - BMP lines must be of lengths divisible by 4.
		{
			for (n = 1; n <= extrabytes; n++)
			{
				fprintf(outfile, "%c", 0);
			}
		}
	}

	fclose(outfile);
}
