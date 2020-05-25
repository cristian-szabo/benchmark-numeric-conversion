#pragma once

#include <charconv>

#include "TestFixture.hpp"

template <typename T>
class Str2NumCharConvFixture : public TestFixture
{
public:

    template <typename...>
    void Setup(std::string number, size_t iterations)
    {
        _number = number;
        _iterations = iterations;
    }

    void Run()
    {
        T result;

        for (size_t i = 0; i < _iterations; ++i)
        {
            std::from_chars(_number.data(), _number.data() + _number.size(), result);
        }
    }

    void Sync()
    {}

private:

    std::string _number;

    size_t _iterations;

};
