#pragma once

#include <sstream>

#include "TestFixture.hpp"

template <typename T>
class Str2NumStreamFixture : public TestFixture
{
public:

    template <typename...>
    void Setup(std::string number, size_t iterations)
    {
        _stream.rdbuf()->str(number);
        _iterations = iterations;
    }

    void Run()
    {
        T result;

        for (size_t i = 0; i < _iterations; ++i)
        {
            _stream >> result;
            _stream.seekg(0, std::ios_base::beg);
        }
    }

    void Sync()
    {}

private:

    std::istringstream _stream;

    size_t _iterations;

};
