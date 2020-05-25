#include "TestException.hpp"

TestException::TestException(std::string message)
	: _message{ message }
{}

const char* TestException::what() const noexcept
{
	return _message.c_str();
}
