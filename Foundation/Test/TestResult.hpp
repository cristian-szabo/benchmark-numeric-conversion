#pragma once

#include <map>
#include <vector>

#include "Profiler.hpp"

class TestResult final
{
public:

    enum class Status
    {
        NotRun,
        Success,
        ExpectedFailure,
        Failed,
        Crashed,
        Disabled
    };

    TestResult() = default;

    explicit TestResult(Status status);

    void SetStatus(Status status);

    Status GetStatus() const;

    void SetMeasurements(const Profiler::Measurements& measurements);

    const Profiler::Measurements& GetMeasurements() const;

private:

    Status _status{ Status::NotRun };

    Profiler::Measurements _measurements;

};
