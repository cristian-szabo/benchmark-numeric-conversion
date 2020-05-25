#include "Dataset.hpp"

Dataset::Dataset(std::string name)
	: _name{ name }
{}

const std::string& Dataset::GetName() const
{
	return _name;
}
