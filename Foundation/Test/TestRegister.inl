#include "TestContext.hpp"

template <typename T>
TestCaseRegister<T>::TestCaseRegister(std::string name, TestCase::Mode mode, TestCase::Status status, std::string description)
{
	TestContext::GetInstance().AddTestCase<T>(name, mode, status, description);
}

template <typename T>
template <typename D>
TestCaseRegister<T>::TestCaseRegister(std::string name, TestCase::Mode mode, TestCase::Status status, D&& dataset)
{
	auto it = dataset.begin();

	for (int i = 0; i < dataset.size(); ++i, ++it)
	{
		TestContext::GetInstance().AddDataTestCase<T>(name, mode, status, it.Description(), *it);
	}
}
