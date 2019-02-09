#include "Start.h"

std::string TStart::enterFileName() {
	std::cout << "Enter file name: ";
	std::string fileName;
	std::cin >> fileName;
	try {
		if (fileName.empty()) {
			throw 1;
		}
		else {
			size_t pos = fileName.find(".ini");
			if (pos == fileName.npos) throw 2;
		}
	}
	catch (int i) {
		switch (i) {
		case 1: {
			std::cout << "Error " << i << " - put the file name" << std::endl;
			enterFileName();
			break;
		}
		case 2: {
			std::cout << "Error " << i << " - wrong file format" << std::endl;
			enterFileName();
			break;
		default: break;
		}
		}
	}
	return fileName;
}
