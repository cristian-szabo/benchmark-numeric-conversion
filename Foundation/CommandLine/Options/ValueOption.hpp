#pragma once

#include "Option.hpp"

#include <sstream>
#include <stdexcept>
#include <string>

template <typename T>
class ValueOption : public Option
{
public:

    ValueOption(std::string name, T defaultValue = T());

    bool Parse(std::string value) override;

    std::string Help() const override;

    const T &GetValue() const;

protected:

    void SetValue(T value);

private:

    T _value{};

};

#include "ValueOption.inl"
