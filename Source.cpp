#include <iostream>
#include "IniParser.h"

int main() {
	try {
		IniParser iniParser;
	}
	catch (const std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
}