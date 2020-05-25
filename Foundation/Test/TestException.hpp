#pragma once

#include <stdexcept>

class TestException : public std::exception
{
public:

	TestException(std::string message);

	const char* what() const noexcept override;

private:

	std::string _message;

};
