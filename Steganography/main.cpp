#include <iostream>
#include "BMPFile.h"
#include "Hider.h"
#include "MyAlgo.h"

int main(int argc, char* argv[]) {
	//auto arr = readBMP("image.bmp");
	BMPFile file("image.bmp");
	file.readFile();
	std::vector<byte> bytes = { 255,128,64 };
	Hider h(new MyAlgo());
	h.pack(&file, &bytes);
	file.saveFile();
	for (int i : h.unpack(&file)) {
		std::cout << "[" << i << "]\n";
	}
	std::cin.get();
}