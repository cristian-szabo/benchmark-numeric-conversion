#include "TestContext.hpp"

#include <sstream>
#include <iterator>
#include <thread>
#include <iostream>
#include <numeric>

#include "TestException.hpp"
#include "Statistics.hpp"
#include "String.hpp"

bool operator<(const TestInfo& lhs, const TestInfo& rhs)
{
	return lhs.id < rhs.id;
}

TestContext& TestContext::GetInstance()
{
	static TestContext instance;
	return instance;
}

void TestContext::SetConfig(TestConfig config)
{
	_config = config;
}

Profiler& TestContext::GetProfiler()
{
	return _profiler;
}

void TestContext::PushTestSuite(std::string name)
{
	_testSuites.emplace_back(std::move(name));
}

void TestContext::PopTestSuite()
{
	_testSuites.pop_back();
}

bool TestContext::Run()
{
    _testResults.clear();

   auto start = std::chrono::high_resolution_clock::now();

    int testIndex = 0;

    for (auto& testCaseFactory : _testCaseFactories)
    {
        const TestInfo testInfo{ testIndex, testCaseFactory->GetName(), testCaseFactory->GetMode(), testCaseFactory->GetStatus() };

        if (!_config.filter.SkipTestCase(testInfo))
        {
            RunTest(testInfo, *testCaseFactory);

			std::this_thread::sleep_for(_config.cooldown);
        }

		testIndex += 1;
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto runtime = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    
	auto results = AnalyzeTestResults();

    std::cout << "Executed " << _testResults.size() << " test(s) ("
        << results[TestResult::Status::Success] << " passed, "
        << results[TestResult::Status::ExpectedFailure] << " expected failures, "
        << results[TestResult::Status::Failed] << " failed, "
        << results[TestResult::Status::Crashed] << " crashed, "
        << results[TestResult::Status::Disabled] << " disabled) in " << runtime.count() << " second(s)\n";

    int numSuccessfulTests = results[TestResult::Status::Success] + results[TestResult::Status::ExpectedFailure] + results[TestResult::Status::Disabled];

    return (static_cast<size_t>(numSuccessfulTests) == _testResults.size());
}

void TestContext::PrintTestInfo()
{
	int testIndex = 0;

	for (const auto& factory : _testCaseFactories)
	{
		TestInfo testInfo{ testIndex, factory->GetName(), factory->GetMode(), factory->GetStatus() };

		if (!_config.filter.SkipTestCase(testInfo))
		{
			std::cout << "[" << testInfo.id << ", " << testInfo.mode << ", " << testInfo.status << "] " << testInfo.name << "\n";
		}

		testIndex += 1;
	}
}

void TestContext::RunTest(const TestInfo& testInfo, TestCaseFactory& testCaseFactory)
{
	if (testCaseFactory.GetStatus() == TestCase::Status::Disabled)
	{
		_testResults.emplace(testInfo, TestResult(TestResult::Status::Disabled));
		
		return;
	}

	std::cout << "Running [" << testInfo.id << "] '" << testInfo.name << "'" << "\n";

	TestResult testResult(TestResult::Status::NotRun);

	const bool isExpectedFailure = (testInfo.status == TestCase::Status::ExpectedFailure);

	try
	{
		auto testCase = testCaseFactory.MakeTestCase();

		try
		{
			_profiler.Setup();

			testCase->Setup();

            for (int i = 0; i < _config.iterations; ++i)
            {
				_profiler.Start();
				testCase->Run();
				testCase->Sync();
				_profiler.Stop();
            }

			testCase->Teardown();

			_profiler.Teardown();

            if (testResult.GetStatus() == TestResult::Status::NotRun)
            {
				testResult.SetStatus(TestResult::Status::Success);
            }
		}
		catch (TestException& ex)
		{
			_profiler.Teardown();

			std::string prefix = isExpectedFailure ? "EXPECTED ERROR: " : "ERROR: ";
			std::cout << prefix << ex.what() << "\n";

			testResult.SetStatus(TestResult::Status::Failed);

			if (_config.throwError)
			{
				throw;
			}
		}
        catch (std::exception& ex)
        {
			_profiler.Teardown();

			std::string prefix = isExpectedFailure ? "EXPECTED ERROR: " : "ERROR: ";
			std::cout << prefix << ex.what() << "\n";

            testResult.SetStatus(TestResult::Status::Crashed);

            if (_config.throwError)
            {
				throw;
            }
        }
		catch (...)
		{
			_profiler.Teardown();

			std::string prefix = isExpectedFailure ? "EXPECTED ERROR: " : "ERROR: ";
			std::cout << prefix << "Received unknown exception!" << "\n";

			testResult.SetStatus(TestResult::Status::Crashed);

			if (_config.throwError)
			{
				throw;
			}
		}
	}
	catch (...)
	{
		std::string prefix = isExpectedFailure ? "EXPECTED ERROR: " : "ERROR: ";
		std::cout << prefix << "Received unknown exception!" << "\n";

		testResult.SetStatus(TestResult::Status::Crashed);

		if (_config.throwError)
		{
			throw;
		}
	}

	if (testResult.GetStatus() == TestResult::Status::Failed)
	{
		if (testInfo.status == TestCase::Status::ExpectedFailure)
		{
			testResult.SetStatus(TestResult::Status::ExpectedFailure);
		}
	}

	if (testResult.GetStatus() == TestResult::Status::Failed || 
		testResult.GetStatus() == TestResult::Status::Crashed)
	{
		if (_config.stopOnError)
		{
			throw std::runtime_error("Abort on first error.");
		}
	}

	auto measurements = _profiler.GetMeasurements();

	for (const auto& instrument : measurements)
	{
		std::cout << "  " << instrument.first << ":";

		Statistics stats(instrument.second);

		std::cout << "    ";
		std::cout << "AVG=" << stats.Mean() << " " << stats.Max().GetUnit();
		
		if (instrument.second.size() > 1)
		{
			std::cout << ", STDDEV=" << std::to_string(stats.StdDev()) << " %";
			std::cout << ", MIN=" << stats.Min();
			std::cout << ", MAX=" << stats.Max();
			std::cout << ", MEDIAN=" << stats.Median().GetValue() << " " << stats.Median().GetUnit();
		}

		std::cout << "\n";
	}

	_profiler.Reset();

	testResult.SetMeasurements(measurements);

	_testResults.emplace(testInfo, testResult);
}

std::map<TestResult::Status, int> TestContext::AnalyzeTestResults()
{
	std::map<TestResult::Status, int> result;

	for (const auto& test : _testResults)
	{
		result[test.second.GetStatus()] += 1;
	}

	return result;
}

std::string TestContext::GetTestSuite()
{
	return JoinString(_testSuites, "/");
}
