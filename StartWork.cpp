#include "StartWork.h"

std::string StartWork(int &flag)
{
	std::cout << "Enter file name: ";
	std::string filename_cstr;
	std::cin >> filename_cstr;
	try {
		if (filename_cstr.empty()) {
			throw 1;
		}
		size_t pos = filename_cstr.find(".ini");
		if (pos == filename_cstr.npos) throw 2;
		else {
			std::ifstream checkiFile(filename_cstr);
			if (checkiFile.is_open()) {
				flag = 0;
				return filename_cstr;
			}
			else throw 3;
		}
	}
	catch (int i) {
		switch (i) {
		case 1: {
			std::cout << "Error #" << i << " - put the file name" << std::endl;
			break;
		}
		case 2: {
			std::cout << "Error #" << i << " - wrong file format" << std::endl;
			break;
		case 3: {
			std::cout << "Error #" << i << " - file not found" << std::endl;
			break;
		}
		default: break;
		}
		}
	}
	return false;
}
