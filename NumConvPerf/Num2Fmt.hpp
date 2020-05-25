#pragma once

#include <inttypes.h>
#include <type_traits>

template <class T, typename Enable = void>
struct Num2Fmt
{};

template <typename T>
struct Num2Fmt<T, std::enable_if_t<std::is_same_v<T, int8_t>>>
{
    static const char* Get()
    {
        return "%" SCNd8;
    }
};

template <typename T>
struct Num2Fmt<T, std::enable_if_t<std::is_same_v<T, uint8_t>>>
{
    static const char* Get()
    {
        return "%" SCNu8;
    }
};

template <typename T>
struct Num2Fmt<T, std::enable_if_t<std::is_same_v<T, int16_t>>>
{
    static const char* Get()
    {
        return "%" SCNd16;
    }
};

template <typename T>
struct Num2Fmt<T, std::enable_if_t<std::is_same_v<T, uint16_t>>>
{
    static const char* Get()
    {
        return "%" SCNu16;
    }
};

template <typename T>
struct Num2Fmt<T, std::enable_if_t<std::is_same_v<T, int32_t>>>
{
    static const char* Get()
    {
        return "%" SCNd32;
    }
};

template <typename T>
struct Num2Fmt<T, std::enable_if_t<std::is_same_v<T, uint32_t>>>
{
    static const char* Get()
    {
        return "%" SCNu32;
    }
};

template <typename T>
struct Num2Fmt<T, std::enable_if_t<std::is_same_v<T, int64_t>>>
{
    static const char* Get()
    {
        return "%" SCNd64;
    }
};

template <typename T>
struct Num2Fmt<T, std::enable_if_t<std::is_same_v<T, uint64_t>>>
{
    static const char* Get()
    {
        return "%" SCNu64;
    }
};

template <typename T>
struct Num2Fmt<T, std::enable_if_t<std::is_same_v<T, float>>>
{
    static const char* Get()
    {
        return "%f";
    }
};

template <typename T>
struct Num2Fmt<T, std::enable_if_t<std::is_same_v<T, double>>>
{
    static const char* Get()
    {
        return "%lf";
    }
};
