#include "TestRegister.hpp"

#include "TestContext.hpp"

TestSuiteRegister::TestSuiteRegister()
{
	TestContext::GetInstance().PopTestSuite();
}

TestSuiteRegister::TestSuiteRegister(std::string name)
{
	TestContext::GetInstance().PushTestSuite(name);
}
