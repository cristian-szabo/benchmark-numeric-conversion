#include "BoolOption.hpp"

BoolOption::BoolOption(std::string name, bool defaultValue)
    : ValueOption<bool>{ std::move(name), defaultValue }
{}

bool BoolOption::Parse(std::string value)
{
    if (value == "true")
    {
        SetValue(true);
        SetDefined(true);
    }
    else if (value == "false")
    {
        SetValue(false);
        SetDefined(true);
    }

    return IsDefined();
}

std::string BoolOption::Help() const
{
    return "--" + GetName() + ", --no-" + GetName() + " - " + GetDescription();
}
