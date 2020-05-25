#pragma once

#include "TestFixture.hpp"

#include "Num2Fmt.hpp"

template <typename T>
class Str2NumScanFixture : public TestFixture
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
            sscanf(_number.c_str(), Num2Fmt<T>::Get(), &result);
        }
    }

    void Sync()
    {}

private:

    std::string _number;

    size_t _iterations;

};
