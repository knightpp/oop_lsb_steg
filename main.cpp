#include <iostream>
#include "hpp/BMPFile.h"
#include "hpp/Hider.h"
#include "hpp/MyAlgo.h"
#include <chrono>

int main(int argc, char* argv[]) {
	//auto arr = readBMP("image.bmp");
    auto start = std::chrono::system_clock::now();
    BMPFile file("image.bmp");
	file.readFile();
	std::vector<byte> bytes = {69,69,69,69,69,69,69};
	Hider h(new MyAlgo());
	h.pack(&file, &bytes);

	for (int i : h.unpack(&file)) {
		std::cout << "[" << i << "]\n";
	}
    auto end = std::chrono::system_clock::now();

	std::cout << "Ms taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    file.saveFile();
}