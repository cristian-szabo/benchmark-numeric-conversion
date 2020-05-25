#include <sstream>

#include "String.hpp"

template <typename T>
ItemDataset<T>::Iterator::Iterator(std::string name, const T* value)
    : _name{ name }, _value{ value }
{}

template <typename T>
std::string ItemDataset<T>::Iterator::Description() const
{
    return _name + "=" + ToString(*_value);
}

template <typename T>
typename ItemDataset<T>::Type ItemDataset<T>::Iterator::operator*() const
{
    return std::make_tuple(*_value);
}

template <typename T>
typename ItemDataset<T>::Iterator& ItemDataset<T>::Iterator::operator++()
{
    return *this;
}

template <typename T>
ItemDataset<T>::ItemDataset(std::string&& name, T&& value)
    : Dataset{ std::move(name) }, _value{ std::forward<T>(value) }
{}

template <typename T>
typename ItemDataset<T>::Iterator ItemDataset<T>::begin() const
{
    return Iterator(GetName(), &_value);
}

template <typename T>
size_t ItemDataset<T>::size() const
{
    return 1;
}

template <typename T>
ItemDataset<T> MakeItem(std::string&& name, T&& value)
{
    return ItemDataset<T>(std::move(name), std::forward<T>(value));
}
