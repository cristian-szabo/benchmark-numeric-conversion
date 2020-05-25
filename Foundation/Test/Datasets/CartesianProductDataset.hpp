#pragma once

#include "Dataset.hpp"

#include <string>
#include <tuple>
#include <utility>

template <typename T, typename U>
class CartesianProductDataset : public Dataset
{
private:

    using NoRefT = std::remove_reference_t<T>;
    using NoRefU = std::remove_reference_t<U>;

    using IterT = typename NoRefT::Iterator;
    using IterU = typename NoRefU::Iterator;

public:

    using Type = decltype(std::tuple_cat(std::declval<typename NoRefT::Type>(), std::declval<typename NoRefU::Type>()));

    class Iterator
    {
    public:

        Iterator(const NoRefT* dataset1, const NoRefU* dataset2);

        std::string Description() const;

        Type operator*() const;

        Iterator& operator++();

    private:

        IterT _iter1;

        NoRefU* _dataset2;

        IterU _iter2;

        int _pos2{ 0 };

    };

    CartesianProductDataset(T&& dataset1, U&& dataset2);

    Iterator begin() const;

    size_t size() const;

private:

    T _dataset1;

    U _dataset2;

};

template <typename T, typename U>
CartesianProductDataset<T, U> Combine(T&& dataset1, U&& dataset2);

#include "CartesianProductDataset.inl"
