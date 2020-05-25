#include "WallClock.hpp"

#include <stdexcept>

WallClock::WallClock(ScaleFactor scaleFactor)
    : Instrument{ scaleFactor }
{
    switch (scaleFactor)
    {
    case ScaleFactor::None:
        _scale_factor = 1.f;
        SetUnit("us");
        break;
    case ScaleFactor::TimeMS:
        _scale_factor = 1000.f;
        SetUnit("ms");
        break;
    case ScaleFactor::TimeS:
        _scale_factor = 1000000.f;
        SetUnit("s");
        break;
    default:
        throw std::runtime_error("Unsupported scale factor!");
    }
};

std::string WallClock::GetId() const
{
    return "Wall Clock";
}

void WallClock::Setup()
{}

void WallClock::Start()
{
    _start = std::chrono::system_clock::now();
}

void WallClock::Stop()
{
    _stop = std::chrono::system_clock::now();
}

void WallClock::Teardown()
{}

Instrument::Measurements WallClock::GetMeasurements() const
{
    Measurements measurements;

    const auto delta = std::chrono::duration_cast<std::chrono::microseconds>(_stop - _start);

    auto measurement = Measurement(delta.count() / _scale_factor, GetUnit());
    measurements.emplace("Time", measurement);

    return measurements;
}
