template <typename T, typename U>
CartesianProductDataset<T, U>::Iterator::Iterator(const NoRefT* dataset1, const NoRefU* dataset2)
    : _iter1{ dataset1->begin() }, _dataset2{ dataset2 }, _iter2{ dataset2->begin() }
{}

template <typename T, typename U>
std::string CartesianProductDataset<T, U>::Iterator::Description() const
{
    return _iter1.Description() + ":" + _iter2.Description();
}

template <typename T, typename U>
typename CartesianProductDataset<T, U>::Type CartesianProductDataset<T, U>::Iterator::operator*() const
{
    return std::tuple_cat(*_iter1, *_iter2);
}

template <typename T, typename U>
typename CartesianProductDataset<T, U>::Iterator& CartesianProductDataset<T, U>::Iterator::operator++()
{
    ++_pos2;

    if (_pos2 < _dataset2->size())
    {
        ++_iter2;
    }
    else
    {
        _pos2 = 0;
        _iter2 = _dataset2->begin();

        ++_iter1;
    }

    return *this;
}

template <typename T, typename U>
CartesianProductDataset<T, U>::CartesianProductDataset(T&& dataset1, U&& dataset2)
    : _dataset1{ std::forward<T>(dataset1) }, _dataset2{ std::forward<U>(dataset2) }
{}

template <typename T, typename U>
typename CartesianProductDataset<T, U>::Iterator CartesianProductDataset<T, U>::begin() const
{
    return Iterator(&_dataset1, &_dataset2);
}

template <typename T, typename U>
size_t CartesianProductDataset<T, U>::size() const
{
    return _dataset1.size() * _dataset2.size();
}

template <typename T, typename U>
CartesianProductDataset<T, U> Combine(T&& dataset1, U&& dataset2)
{
    return CartesianProductDataset<T, U>(std::forward<T>(dataset1), std::forward<U>(dataset2));
}
