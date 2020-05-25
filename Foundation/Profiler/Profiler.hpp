#pragma once

#include "Measurement.hpp"
#include "Instrument.hpp"

#include <map>
#include <vector>
#include <memory>

class Profiler final
{
public:

    using Measurements = std::map<std::string, std::vector<Measurement>>;

    void AddInstrument(std::unique_ptr<Instrument> instrument);

    void Setup();

    void Start();

    void Stop();

    void Teardown();

    void Reset();

    const Measurements& GetMeasurements() const;

private:

    std::vector<std::unique_ptr<Instrument>> _instruments{};

    Measurements _measurements{};

};
