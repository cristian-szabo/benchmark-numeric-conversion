#include "Instrument.hpp"

Instrument::Instrument(ScaleFactor scaleFactor)
{}

void Instrument::SetUnit(std::string unit)
{
	_unit = unit;
}

const std::string& Instrument::GetUnit() const
{
	return _unit;
}
