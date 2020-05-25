#include "String.hpp"

template <typename T>
inline EnumOption<T>::EnumOption(std::string name, T defaultValue, std::set<T> allowedValues)
    : ValueOption<T>{ std::move(name), std::move(defaultValue) }, _allowedValues{ std::move(allowedValues) }
{}

template <typename T>
inline bool EnumOption<T>::Parse(std::string value)
{
    std::stringstream stream{ value };
    
    T v{};
    stream >> v;

    if (!stream.fail())
    {
        if (_allowedValues.count(v))
        {
            ValueOption<T>::SetValue(std::move(v));
            Option::SetDefined(true);
        }
    }

    return Option::IsDefined();
}

template <typename T>
inline std::string EnumOption<T>::Help() const
{
    std::stringstream msg;
    msg << "--" + Option::GetName() + "={";
    msg << JoinString(_allowedValues, ",");
    msg << "} - " << Option::GetDescription();

    return msg.str();
}
