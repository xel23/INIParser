#include "IniParser.h"

IniParser::IniParser()
{
	std::cout << "Enter file name: ";
	std::string filename_cstr;
	std::cin >> filename_cstr;
	if (filename_cstr.empty()) {
		throw EmptyFileName("File name is empty");
	}
	size_t pos = filename_cstr.find(".ini");
	if (pos == filename_cstr.npos) throw WrongFileFormat("Wrong file format");
	else {
		std::ifstream checkiFile(filename_cstr);
		if (checkiFile.is_open()) {
			Initialize(filename_cstr.c_str());
		}
		else throw FileNotFound("File not found");
	}
}

void IniParser::Initialize(const char * filename_cstr) {
	std::cout << "File was opened. Reading..." << std::endl;
	std::ifstream fileIn(filename_cstr, std::ifstream::in);
	std::string str, sectionName;
	while (std::getline(fileIn, str)) {
		if (str[0] == '[') {
			sectionName = str;
			size_t first = str.find('[');
			size_t last = str.find(']');

			if (first != std::string::npos)
			{
				std::string section(str, ++first, last - first);
				sectionName = section;
			}
		}
		else {
			if ((str[0] >= 'A' && str[0] <= 'z') || (str[0] >= '0' && str[0] <= '9')) { // clear param field and put in storage
				std::string lsh, rsh;
				std::size_t pos = str.find('=');
				lsh = str.substr(0, pos);
				rsh = str.substr(pos + 1);
				pos = lsh.find(' ');
				lsh = lsh.substr(0, pos);
				pos = rsh.find_first_not_of(' ');
				rsh = rsh.substr(pos);
				pos = rsh.find(' ');
				rsh = rsh.substr(0, pos);
				std::map<std::string, std::string> tmpPair;
				tmpPair[lsh] = rsh;
				storage.insert(std::make_pair(sectionName, tmpPair));
			}
		}
	}
	std::cout << "Reading is successfully." << std::endl;
	Menu();
}

void IniParser::Menu() const
{
	std::cout << "Enter section name (without []): ";
	std::string section_name, param_name;
	std::cin >> section_name;
		if (IsHaveSection(section_name.c_str())) {
			std::cout << "Enter param name: ";
			std::cin >> param_name;
			if (IsHaveParam(section_name.c_str(), param_name.c_str())) {
				std::cout << "Enter type (1 - ineger; 2 - double; 3 - string): ";
				int type;
				std::cin >> type;
				if (type > 3 || type < 1) throw WrongType("Wrong type");
				if (type == 1) std::cout << GetValue<int>(section_name.c_str(), param_name.c_str()) << std::endl;
				else if (type == 2) std::cout << GetValue<double>(section_name.c_str(), param_name.c_str()) << std::endl;
				else std::cout << GetValue<std::string>(section_name.c_str(), param_name.c_str()) << std::endl;
			}
			else throw WrongSectionParam("Wrong pair [" + section_name + " - " + param_name + "]");
		}
	else throw WrongSectionName("Wrong section name: " + section_name);
}

bool IniParser::IsHaveSection(const char * section_name) const
{
	if (storage.find(section_name) != storage.end()) return true;
	return false;
}

bool IniParser::IsHaveParam(const char * section_name, const char * param_name) const
{
	std::multimap<std::string, std::map<std::string, std::string>>::const_iterator it = storage.find(section_name);
	while (it != storage.end()) {
		if (it->second.find(param_name) != it->second.end()) {
			return true;
		}
		else ++it;
	}
	return false;
}

int IniParser::GetValueInt(const char * section_name, const char * param_name) const
{
	std::multimap<std::string, std::map<std::string, std::string>>::const_iterator it = storage.find(section_name);
	while (it != storage.end()) {
		if (it->second.find(param_name) != it->second.end()) {
			return atoi(it->second.find(param_name)->second.c_str());
		}
		else ++it;
	}
}

double IniParser::GetValueDouble(const char * section_name, const char * param_name) const
{
	std::multimap<std::string, std::map<std::string, std::string>>::const_iterator it = storage.find(section_name);
	while (it != storage.end()) {
		if (it->second.find(param_name) != it->second.end()) {
			return atof(it->second.find(param_name)->second.c_str());
		}
		else ++it;
	}
}

std::string IniParser::GetValueString(const char * section_name, const char * param_name) const
{
	std::multimap<std::string, std::map<std::string, std::string>>::const_iterator it = storage.find(section_name);
	while (it != storage.end()) {
		if (it->second.find(param_name) != it->second.end()) {
			return it->second.find(param_name)->second;
		}
		else ++it;
	}
}