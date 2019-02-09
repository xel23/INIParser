#include "ExceptionList.h"

ParserException::ParserException(const std::string & message) noexcept : text_err(message) {}
const char * ParserException::what() const noexcept
{
	return text_err.c_str();
};