#include <memory>

template <typename T>
void TestContext::AddTestCase(std::string name, TestCase::Mode mode, TestCase::Status status, std::string description)
{
	_testCaseFactories.emplace_back(std::make_unique<SimpleTestCaseFactory<T>>(GetTestSuite(), name, mode, status, description));
}

template <typename T, typename D>
void TestContext::AddDataTestCase(std::string name, TestCase::Mode mode, TestCase::Status status, std::string description, D data)
{
	_testCaseFactories.emplace_back(std::make_unique<DataTestCaseFactory<T, D>>(GetTestSuite(), name, mode, status, description, std::move(data)));
}
