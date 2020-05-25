template <typename T>
Measurement::Measurement(T v, std::string unit, std::list<std::string> rawData)
	: _value{ v }, _unit{ unit }, _rawData{ rawData }
{}

template <typename T, std::enable_if_t<std::is_floating_point_v<T>, size_t>>
Measurement::Value::Value(T v)
	: _data{ static_cast<double>(v) }
{}

template <typename T, std::enable_if_t<std::is_integral_v<T>, size_t>>
Measurement::Value::Value(T v)
	: _data{ static_cast<int64_t>(v) }
{}
