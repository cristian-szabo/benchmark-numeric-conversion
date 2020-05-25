#include "Profiler.hpp"

void Profiler::AddInstrument(std::unique_ptr<Instrument> instrument)
{
	_instruments.emplace_back(std::move(instrument));
}

void Profiler::Setup()
{
    for (auto& instrument : _instruments)
    {
        instrument->Setup();
    }
}

void Profiler::Start()
{
    for (auto& instrument : _instruments)
    {
        instrument->Start();
    }
}

void Profiler::Stop()
{
    for (auto instrument = _instruments.rbegin(); instrument != _instruments.rend(); instrument++)
    {
        (*instrument)->Stop();
    }

    for (auto& instrument : _instruments)
    {
        for (auto& measurement : instrument->GetMeasurements())
        {
            _measurements[instrument->GetId() + "/" + measurement.first].push_back(measurement.second);
        }
    }
}

void Profiler::Teardown()
{
    for (auto instrument = _instruments.rbegin(); instrument != _instruments.rend(); instrument++)
    {
        (*instrument)->Teardown();
    }
}

void Profiler::Reset()
{
    _measurements.clear();
}

const Profiler::Measurements& Profiler::GetMeasurements() const
{
	return _measurements;
}
