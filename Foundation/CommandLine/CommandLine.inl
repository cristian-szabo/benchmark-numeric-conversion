template <typename T, typename... As>
inline T* CommandLine::AddOption(const std::string& name, As&&... args)
{
    auto result = _options.emplace(name, std::make_unique<T>(name, std::forward<As>(args)...));
    return static_cast<T*>(result.first->second.get());
}

template <typename T, typename... As>
inline T* CommandLine::AddPositionalOption(As&&... args)
{
    _positionalOptions.emplace_back(std::make_unique<T>(std::forward<As>(args)...));
    return static_cast<T*>(_positionalOptions.back().get());
}
