#pragma once

#include <vector>
#include <optional>

#include "Measurement.hpp"

class Statistics
{
public:

    Statistics(const std::vector<Measurement>& measurements);

    const Measurement& Min() const;

    const Measurement& Max() const;

    const Measurement& Median() const;

    const Measurement::Value& Mean() const;

    double StdDev() const;

private:

    std::optional<Measurement> _min;

    std::optional<Measurement> _max;

    std::optional<Measurement> _median;

    Measurement::Value _mean{ 0.0 };

    double _stddev{ 0.0 };

};
