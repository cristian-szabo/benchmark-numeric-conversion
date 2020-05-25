template <typename T>
SimpleTestCaseFactory<T>::SimpleTestCaseFactory(std::string suiteName, std::string testName, TestCase::Mode mode, TestCase::Status status, std::string description)
	: TestCaseFactory{ suiteName, testName, mode, status, description }
{}

template <typename T>
std::unique_ptr<TestCase> SimpleTestCaseFactory<T>::MakeTestCase() const
{
	return std::make_unique<T>();
}

template <typename T, typename D>
DataTestCaseFactory<T, D>::DataTestCaseFactory(std::string suiteName, std::string testName, TestCase::Mode mode, TestCase::Status status, std::string description, D&& data)
	: TestCaseFactory{ suiteName, testName, mode, status, description }, _data{ std::move(data) }
{}

template <typename T, typename D>
std::unique_ptr<TestCase> DataTestCaseFactory<T, D>::MakeTestCase() const
{
	return std::make_unique<T>(_data);
}
