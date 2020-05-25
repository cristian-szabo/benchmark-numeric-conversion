#pragma once

#include <map>

#include "Measurement.hpp"

class Instrument
{
public:

    using Measurements = std::map<std::string, Measurement>;
    
    enum class ScaleFactor
    {
        None,
        Scale1K,
        Scale1M,
        TimeUS,
        TimeMS,
        TimeS,
    };

    Instrument(ScaleFactor scaleFactor);

    virtual ~Instrument() = default;

    virtual std::string GetId() const = 0;

    virtual void Setup() = 0;

    virtual void Start() = 0;

    virtual void Stop() = 0;

    virtual void Teardown() = 0;

    virtual Measurements GetMeasurements() const = 0;

protected:

    void SetUnit(std::string unit);

    const std::string& GetUnit() const;

private:

    std::string _unit{};

};
