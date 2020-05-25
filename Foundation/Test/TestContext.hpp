#pragma once

#include <string>
#include <stack>
#include <vector>
#include <memory>
#include <chrono>
#include <map>

#include "TestCase.hpp"
#include "TestCaseFactory.hpp"
#include "TestFilter.hpp"
#include "TestResult.hpp"

#include "Profiler.hpp"

struct TestInfo
{
	int id;

	std::string name;

	TestCase::Mode mode;

	TestCase::Status status;
};

bool operator<(const TestInfo& lhs, const TestInfo& rhs);

struct TestConfig
{
	TestFilter filter{ TestCase::Mode::All, ".*", "..." };

	size_t iterations{ 1 };

	bool throwError{ false };

	bool stopOnError{ true };

	std::chrono::seconds cooldown{ std::chrono::seconds(1) };
};

class TestContext final
{
public:

	static TestContext& GetInstance();

	void SetConfig(TestConfig config);

	Profiler& GetProfiler();

    void PushTestSuite(std::string name);

    void PopTestSuite();

    template <typename T>
    void AddTestCase(std::string name, TestCase::Mode mode, TestCase::Status status, std::string description);

    template <typename T, typename D>
    void AddDataTestCase(std::string name, TestCase::Mode mode, TestCase::Status status, std::string description, D data);

	bool Run();

	void PrintTestInfo();

private:

	TestConfig _config;

	Profiler _profiler;

	std::vector<std::string> _testSuites{};

	std::vector<std::unique_ptr<TestCaseFactory>> _testCaseFactories{};

	std::map<TestInfo, TestResult> _testResults{};

	TestContext() = default;

	TestContext(const TestContext&) = delete;

	TestContext& operator=(const TestContext&) = delete;

	void RunTest(const TestInfo& testInfo, TestCaseFactory& testCaseFactory);

	std::map<TestResult::Status, int> AnalyzeTestResults();

	std::string GetTestSuite();

};

#include "TestContext.inl"
