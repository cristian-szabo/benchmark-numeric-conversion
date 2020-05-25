#include <sstream>

#include "String.hpp"

template <typename T>
inline VectorDataset<T>::Iterator::Iterator(std::string name, ConstIterator iterator)
    : _name{ name }, _iterator{ iterator }
{}

template <typename T>
inline std::string VectorDataset<T>::Iterator::Description() const
{
    return _name + "=" + ToString(*_iterator);
}

template <typename T>
inline typename VectorDataset<T>::Type VectorDataset<T>::Iterator::operator*() const
{
    return std::make_tuple(*_iterator);
}

template <typename T>
inline typename VectorDataset<T>::Iterator& VectorDataset<T>::Iterator::operator++()
{
    ++_iterator;
    return *this;
}

template <typename T>
inline VectorDataset<T>::VectorDataset(std::string&& name, std::vector<T>&& vector)
    : Dataset{ std::move(name) }, _vector{ std::move(vector) }
{}

template <typename T>
inline typename VectorDataset<T>::Iterator VectorDataset<T>::begin() const
{
    return Iterator(GetName(), _vector.cbegin());
}

template <typename T>
inline size_t VectorDataset<T>::size() const
{
    return _vector.size();
}

template <typename T, typename... Args, typename V>
inline VectorDataset<V> MakeVec(std::string&& name, Args&&... args)
{
    std::vector<V> vec;
    vec.reserve(sizeof...(Args));
    ((vec.emplace_back(std::forward<Args>(args))), ...);
    return VectorDataset<V>(std::move(name), std::move(vec));
}
