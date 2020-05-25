#pragma once

#include "TestFixture.hpp"

#include "TypeTraits.hpp"

template <class T, typename Enable = void>
struct str2num
{};

template <typename T>
struct str2num<T, std::enable_if_t<is_any_of_v<T, int8_t, int16_t, int32_t, uint8_t, uint16_t, uint32_t>>>
{
    static T Run(const std::string& num)
    {
        return std::stoi(num);
    }
};

template <typename T>
struct str2num<T, std::enable_if_t<std::is_same_v<T, int64_t>>>
{
    static T Run(const std::string& num)
    {
        return std::stoll(num);
    }
};

template <typename T>
struct str2num<T, std::enable_if_t<std::is_same_v<T, uint64_t>>>
{
    static T Run(const std::string& num)
    {
        return std::stoull(num);
    }
};

template <typename T>
struct str2num<T, std::enable_if_t<std::is_same_v<T, float>>>
{
    static T Run(const std::string& num)
    {
        return std::stof(num);
    }
};

template <typename T>
struct str2num<T, std::enable_if_t<std::is_same_v<T, double>>>
{
    static T Run(const std::string& num)
    {
        return std::stod(num);
    }
};

template <typename T>
class Str2NumStringFixture : public TestFixture
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
        for (size_t i = 0; i < _iterations; ++i)
        {
            str2num<T>::Run(_number);
        }
    }

    void Sync()
    {}

private:

    std::string _number;

    size_t _iterations;

};
