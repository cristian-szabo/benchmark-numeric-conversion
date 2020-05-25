
#include "ValueOption.hpp"

#include <set>
#include <sstream>
#include <stdexcept>
#include <string>

template <typename T>
class EnumOption : public ValueOption<T>
{
public:

    EnumOption(std::string name, T defaultValue, std::set<T> allowedValues);

    bool Parse(std::string value) override;

    std::string Help() const override;

private:

    std::set<T> _allowedValues{};

};

#include "EnumOption.inl"
