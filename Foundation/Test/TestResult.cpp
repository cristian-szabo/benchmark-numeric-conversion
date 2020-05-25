#include "TestResult.hpp"

TestResult::TestResult(Status status)
	: _status{ status }
{}

void TestResult::SetStatus(Status status)
{
	_status = status;
}

TestResult::Status TestResult::GetStatus() const
{
	return _status;
}

void TestResult::SetMeasurements(const Profiler::Measurements& measurements)
{
	_measurements = measurements;
}

const Profiler::Measurements& TestResult::GetMeasurements() const
{
	return _measurements;
}
