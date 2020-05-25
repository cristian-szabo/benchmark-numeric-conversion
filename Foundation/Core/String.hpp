#pragma once

#include <string>
#include <sstream>
#include <numeric>

template <typename T>
std::string ToString(const T& value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}

template <typename T>
std::string JoinString(const T& container, std::string separator)
{
    auto JoinString = [&](std::string& ss, const auto& s)
    {
        return ss.empty() ? ToString(s) : ss + separator + ToString(s);
    };

    return std::accumulate(container.begin(), container.end(), std::string(), JoinString);
}
