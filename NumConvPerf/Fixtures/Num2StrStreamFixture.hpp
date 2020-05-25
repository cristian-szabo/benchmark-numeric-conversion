#pragma once

#include <sstream>

#include "TestFixture.hpp"

template <typename T>
class Num2StrStreamFixture : public TestFixture
{
public:

    template <typename...>
    void Setup(T number, size_t iterations)
    {
        _number = number;
        _iterations = iterations;
        _stream.clear();
    }

    void Run()
    {
        for (size_t i = 0; i < _iterations; ++i)
        {
            _stream << _number;
            _stream.seekp(0, std::ios_base::beg);
        }
    }

    void Sync()
    {}

private:

    T _number;

    std::ostringstream _stream;

    size_t _iterations;

};
