#include "Option.hpp"

Option::Option(std::string name)
    : _name{ std::move(name) }
{
}

Option::Option(std::string name, bool required, bool defined)
    : _name{ std::move(name) }, _required{ required }, _defined{ defined }
{}

const std::string& Option::GetDescription() const
{
    return _description;
}

const std::string& Option::GetName() const
{
    return _name;
}

void Option::SetRequired(bool required)
{
    _required = required;
}

void Option::SetDefined(bool defined)
{
    _defined = defined;
}

void Option::SetDescription(std::string description)
{
    _description = std::move(description);
}

bool Option::IsRequired() const
{
    return _required;
}

bool Option::IsDefined() const
{
    return _defined;
}
