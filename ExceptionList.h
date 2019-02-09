#pragma once
#include <exception>
#include <string>


class ParserException : public std::exception {
private:
	std::string text_err;
public:
	ParserException(const std::string &message) noexcept;
	~ParserException() {};
	const char * what() const noexcept;
};

class EmptyFileName : public ParserException {
public:
	EmptyFileName(const std::string &message) noexcept : ParserException(message) {};
};

class WrongFileFormat : public ParserException {
public:
	WrongFileFormat(const std::string &message) noexcept : ParserException(message) {};
};

class FileNotFound : public ParserException {
public:
	FileNotFound(const std::string &message) noexcept : ParserException(message) {};
};

class WrongSectionName : public ParserException {
public:
	WrongSectionName(const std::string &message) noexcept : ParserException(message) {};
};

class WrongSectionParam : public ParserException {
public:
	WrongSectionParam(const std::string &message) noexcept : ParserException(message) {};
};

class WrongType : public ParserException {
public:
	WrongType(const std::string &message) noexcept : ParserException(message) {};
};