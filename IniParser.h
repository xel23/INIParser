#pragma once
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <fstream>
#include "ExceptionList.h"


class IniParser {
public:
	IniParser();
	~IniParser() {};
	
	void Initialize(const char* filename_cstr); // Opens Ini file.

	void Menu() const; // Start working
	
	bool IsHaveSection(const char* section_name) const; // Checks if a section exists.
	
	bool IsHaveParam(const char* section_name, const char* param_name) const; // Checks if a pair param-section exists.
	
	template<class T>
	T GetValue(const char* section_name, const char* param_name) const;
	template<> int GetValue(const char* section_name, const char* param_name) const; // Get int value
	template<> double GetValue(const char* section_name, const char* param_name) const; // Get double value
	template<> std::string GetValue(const char* section_name, const char* param_name) const; // Get string value
private:
	std::multimap<std::string, std::map<std::string, std::string>> storage; // storage for data
};

template<class T>
inline T IniParser::GetValue(const char * section_name, const char * param_name) const
{
	throw WrongType("Wrong Type");
}

template<>
inline std::string IniParser::GetValue<std::string>(const char* section_name, const char* param_name) const {
	std::multimap<std::string, std::map<std::string, std::string>>::const_iterator it = storage.find(section_name);
	while (it != storage.end()) {
		if (it->second.find(param_name) != it->second.end()) {
			return it->second.find(param_name)->second;
		}
		else ++it;
	}
}

template<>
inline int IniParser::GetValue<int>(const char* section_name, const char* param_name) const {
	return atoi(GetValue<std::string>(section_name, param_name).c_str());
}

template<>
inline double IniParser::GetValue<double>(const char* section_name, const char* param_name) const {
	return atof(GetValue<std::string>(section_name, param_name).c_str());
}