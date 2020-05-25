#pragma once

#include <string>

#include "TestFixture.hpp"

#include "Num2Fmt.hpp"

template <typename T>
class Num2StrPrintFixture : public TestFixture
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
            sprintf(_buffer.data(), Num2Fmt<T>::Get(), _number);
        }
    }

    void Sync()
    {}

private:

    T _number;

    std::string _buffer;

    size_t _iterations;

};
