#pragma once

#include "ValueOption.hpp"

#include <string>

class BoolOption : public ValueOption<bool>
{
public:

    explicit BoolOption(std::string name, bool defaultValue = false);

    bool Parse(std::string value) override;

    std::string Help() const override;

};
