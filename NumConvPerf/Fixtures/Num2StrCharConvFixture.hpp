#pragma once

#include <charconv>
#include <string>

#include "TestFixture.hpp"

template <typename T>
class Num2StrCharConvFixture : public TestFixture
{
public:

    template <typename...>
    void Setup(T number, size_t iterations)
    {
        _number = number;
        _iterations = iterations;
        _buffer.resize(256);
    }

    void Run()
    {
        for (size_t i = 0; i < _iterations; ++i)
        {
            std::to_chars(_buffer.data(), _buffer.data() + _buffer.size(), _number);
        }
    }

    void Sync()
    {}

private:

    T _number;

    std::string _buffer;

    size_t _iterations;

};
