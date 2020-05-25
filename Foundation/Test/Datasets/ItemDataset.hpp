#pragma once

#include "Dataset.hpp"

template <typename T>
class ItemDataset : public Dataset
{
public:

    using Type = std::tuple<T>;

    class Iterator
    {
    public:

        Iterator(std::string name, const T* value);

        std::string Description() const;

        Type operator*() const;

        Iterator& operator++();

    private:

        std::string _name;

        const T* _value;

    };

    ItemDataset(std::string&& name, T&& value);

    Iterator begin() const;

    size_t size() const;

private:

    T _value;

};

template <typename T>
ItemDataset<T> MakeItem(std::string&& name, T&& value);

#include "ItemDataset.inl"
