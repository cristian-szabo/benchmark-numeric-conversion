#pragma once

#include "Instrument.hpp"

#include <chrono>

class WallClock : public Instrument
{
public:

    WallClock(ScaleFactor scaleFactor);

    std::string GetId() const override;

    void Setup() override;

    void Start() override;

    void Stop() override;

    void Teardown() override;

    Measurements GetMeasurements() const override;

private:

    float _scale_factor{};

    std::chrono::system_clock::time_point _start{};

    std::chrono::system_clock::time_point _stop{};

};
