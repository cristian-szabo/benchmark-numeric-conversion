#include "TestCaseFactory.hpp"

TestCaseFactory::TestCaseFactory(std::string suiteName, std::string testName, TestCase::Mode mode, TestCase::Status status, std::string description)
    : _suiteName{ suiteName }, _testName{ testName }, _mode{ mode }, _status{ status }, _description{ description }
{}

std::string TestCaseFactory::GetName() const
{
    std::string name = _suiteName + "/" + _testName;

    if (!_description.empty())
    {
        name += "@" + _description;
    }

    return name;
}

TestCase::Mode TestCaseFactory::GetMode() const
{
	return _mode;
}

TestCase::Status TestCaseFactory::GetStatus() const
{
	return _status;
}
