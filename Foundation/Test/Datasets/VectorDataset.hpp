#pragma once

#include <vector>

#include "Dataset.hpp"

template <typename T>
class VectorDataset : public Dataset
{
public:

    using Type = std::tuple<T>;

    class Iterator
    {
        using ConstIterator = typename std::vector<T>::const_iterator;

    public:

        Iterator(std::string name, ConstIterator iterator);

        std::string Description() const;

        Type operator*() const;

        Iterator& operator++();

    private:

        std::string _name;

        ConstIterator _iterator;

    };

    VectorDataset(std::string&& name, std::vector<T>&& vector);

    Iterator begin() const;

    size_t size() const;

private:

    std::vector<T> _vector;

};

template <typename T = void, typename... Args, typename V = std::common_type_t<Args...>>
VectorDataset<V> MakeVec(std::string&& name, Args&&... args);

#include "VectorDataset.inl"
