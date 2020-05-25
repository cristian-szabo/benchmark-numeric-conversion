template <typename T>
inline ValueOption<T>::ValueOption(std::string name, T defaultValue)
    : Option{ std::move(name), false, true }, _value{ std::move(defaultValue) }
{}

template <typename T>
inline bool ValueOption<T>::Parse(std::string value)
{
    std::stringstream stream{ std::move(value) };

    int64_t v;
    stream >> v;

    if (!stream.fail())
    {
        _value = T(v);
        SetDefined(true);
    }

    return IsDefined();
}

template <typename T>
inline std::string ValueOption<T>::Help() const
{
    return "--" + GetName() + "=VALUE - " + GetDescription();
}

template <>
inline bool ValueOption<std::string>::Parse(std::string value)
{
    SetValue(std::move(value));
    SetDefined(true);
    return true;
}

template <typename T>
inline const T& ValueOption<T>::GetValue() const
{
    return _value;
}

template <typename T>
inline void ValueOption<T>::SetValue(T value)
{
    _value = std::move(value);
}
