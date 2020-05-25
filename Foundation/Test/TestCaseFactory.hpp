#pragma once

#include <string>
#include <memory>

#include "TestCase.hpp"

class TestCaseFactory
{
public:

    TestCaseFactory(std::string suiteName, std::string testName, TestCase::Mode mode, TestCase::Status status, std::string description = "");

    virtual ~TestCaseFactory() = default;

    std::string GetName() const;

    TestCase::Mode GetMode() const;

    TestCase::Status GetStatus() const;

    virtual std::unique_ptr<TestCase> MakeTestCase() const = 0;

private:

    std::string _suiteName;

    std::string _testName;

    std::string _description;

    TestCase::Mode _mode{ TestCase::Mode::All };

    TestCase::Status _status{ TestCase::Status::Active };

};

template <typename T>
class SimpleTestCaseFactory final : public TestCaseFactory
{
public:

    SimpleTestCaseFactory(std::string suiteName, std::string testName, TestCase::Mode mode, TestCase::Status status, std::string description);

    std::unique_ptr<TestCase> MakeTestCase() const override;

};

template <typename T, typename D>
class DataTestCaseFactory final : public TestCaseFactory
{
public:

    DataTestCaseFactory(std::string suiteName, std::string testName, TestCase::Mode mode, TestCase::Status status, std::string description, D&& data);

    std::unique_ptr<TestCase> MakeTestCase() const override;

private:

    D _data;

};

#include "TestCaseFactory.inl"
