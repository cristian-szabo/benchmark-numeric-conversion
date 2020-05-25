#pragma once

#include <string>

#include "TestFixture.hpp"

template <typename T>
class Num2StrStringFixture : public TestFixture
{
public:

    template <typename...>
    void Setup(T number, size_t iterations)
    {
        _number = number;
        _iterations = iterations;
    }

    void Run()
    {
        std::string result;

        for (size_t i = 0; i < _iterations; ++i)
        {
            result = std::to_string(_number);
        }
    }

    void Sync()
    {}

private:

    T _number;

    size_t _iterations;

};
