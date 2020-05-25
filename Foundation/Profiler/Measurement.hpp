#pragma once

#include <string>
#include <list>
#include <variant>
#include <type_traits>

class Measurement final
{
public:

    class Value
    {
    public:

        template <typename T, std::enable_if_t<std::is_floating_point_v<T>, size_t> = 0>
        Value(T value);

        template <typename T, std::enable_if_t<std::is_integral_v<T>, size_t> = 0>
        Value(T value);

        operator double() const;

        Value operator+(Value b) const;

        Value operator-(Value b) const;

        Value operator*(Value b) const;

        Value operator/(size_t b) const;

        Value& operator-=(const Value& b);

        bool operator<(const Value& b) const;

        const std::variant<int64_t, double>& GetData() const;

    private:

        std::variant<int64_t, double> _data;

    };

    Measurement() = default;

    template <typename T>
    explicit Measurement(T v, std::string unit, std::list<std::string> rawData = {});

    const std::string& GetUnit() const;

    const std::list<std::string>& GetRawData() const;

    const Value& GetValue() const;

    bool operator<(const Measurement& m) const;

private:

    std::string _unit;

    std::list<std::string> _rawData;

    Value _value;

};

std::ostream& operator<<(std::ostream& os, const Measurement::Value& measurement);

std::ostream& operator<<(std::ostream& os, const Measurement& measurement);

#include "Measurement.inl"
