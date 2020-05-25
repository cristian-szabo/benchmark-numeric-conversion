template <typename T>
DataTestCase<T>::DataTestCase(T data)
	: _data{ std::move(data) }
{}

template <typename T>
const T& DataTestCase<T>::GetData() const
{
	return _data;
}
