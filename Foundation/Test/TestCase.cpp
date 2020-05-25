#include "TestCase.hpp"

#include <map>
#include <string>
#include <algorithm>

void TestCase::Setup()
{}

void TestCase::Run()
{}

void TestCase::Sync()
{}

void TestCase::Teardown()
{}

std::istream& operator>>(std::istream& is, TestCase::Mode& mode)
{
    static const std::map<std::string, TestCase::Mode> modeMap =
    {
        { "all", TestCase::Mode::All },
        { "disabled", TestCase::Mode::Disabled },
        { "precommit", TestCase::Mode::PreCommit },
        { "nightly", TestCase::Mode::Nightly },
    };

    std::string str;
    is >> str;

    std::transform(str.begin(), str.end(), str.begin(),
        [](std::string::value_type c) { return std::tolower(c); });

    try
    {
        mode = modeMap.at(str);
    }
    catch (const std::out_of_range&)
    {
        throw std::invalid_argument(str);
    }

	return is;
}

std::istream& operator>>(std::istream& is, TestCase::Status& status)
{
    static const std::map<std::string, TestCase::Status> statusMap =
    {
        { "active", TestCase::Status::Active },
        { "disabled", TestCase::Status::Disabled },
        { "expected_failure", TestCase::Status::ExpectedFailure }
    };

    std::string str;
    is >> str;

    std::transform(str.begin(), str.end(), str.begin(),
        [](std::string::value_type c) { return std::tolower(c); });

    try
    {
        status = statusMap.at(str);
    }
    catch (const std::out_of_range&)
    {
        throw std::invalid_argument(str);
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, TestCase::Mode mode)
{
    switch (mode)
    {
    case TestCase::Mode::Disabled:
        os << "DISABLED";
        break;
    case TestCase::Mode::PreCommit:
        os << "PRECOMMIT";
        break;
    case TestCase::Mode::Nightly:
        os << "NIGHTLY";
        break;
    case TestCase::Mode::All:
        os << "ALL";
        break;
    default:
        throw std::invalid_argument("Unsupported mode");
    }

	return os;
}

std::ostream& operator<<(std::ostream& os, TestCase::Status status)
{
    switch (status)
    {
    case TestCase::Status::Active:
        os << "ACTIVE";
        break;
    case TestCase::Status::Disabled:
        os << "DISABLED";
        break;
    case TestCase::Status::ExpectedFailure:
        os << "EXPECTED_FAILURE";
        break;
    default:
        throw std::invalid_argument("Unsupported status");
    }

    return os;
}
