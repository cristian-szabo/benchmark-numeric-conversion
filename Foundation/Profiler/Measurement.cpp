#include "Measurement.hpp"

#include <ostream>

Measurement::Value::operator double() const
{
	return std::visit([](auto x) -> double { return x; }, _data);
}

Measurement::Value Measurement::Value::operator+(Value b) const
{
	return std::visit([](auto x, auto y) -> Measurement::Value { return x + y; }, _data, b._data);
}

Measurement::Value Measurement::Value::operator-(Value b) const
{
	return std::visit([](auto x, auto y) -> Measurement::Value { return x - y; }, _data, b._data);
}

Measurement::Value Measurement::Value::operator*(Value b) const
{
	return std::visit([](auto x, auto y) -> Measurement::Value { return x * y; }, _data, b._data);
}

Measurement::Value Measurement::Value::operator/(size_t b) const
{
	return std::visit([&](auto x) -> Measurement::Value { return x / b; }, _data);
}

Measurement::Value& Measurement::Value::operator-=(const Value& b)
{
	std::visit([](auto& x, auto y) { x -= y; }, _data, b._data);
	return *this;
}

bool Measurement::Value::operator<(const Value& b) const
{
	return std::visit([](auto x, auto y) -> bool { return x < y; }, _data, b._data);
}

const std::variant<int64_t, double>& Measurement::Value::GetData() const
{
	return _data;
}

const std::string& Measurement::GetUnit() const
{
	return _unit;
}

const std::list<std::string>& Measurement::GetRawData() const
{
	return _rawData;
}

const Measurement::Value& Measurement::GetValue() const
{
	return _value;
}

bool Measurement::operator<(const Measurement& m) const
{
	return _value < m._value;
}

std::ostream& operator<<(std::ostream& os, const Measurement::Value& value)
{
	std::visit([&](const auto& arg) { os << arg; }, value.GetData());
	return os;
}

std::ostream& operator<<(std::ostream& os, const Measurement& measurement)
{
	os << measurement.GetValue() << " " << measurement.GetUnit();
	return os;
}
