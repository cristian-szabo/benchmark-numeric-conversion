#include "Statistics.hpp"

#include <algorithm>
#include <numeric>
#include <cmath>

template <typename T>
std::vector<size_t> sort_indices(const std::vector<T>& v)
{
	std::vector<size_t> idx(v.size());
	std::iota(idx.begin(), idx.end(), 0);

	std::sort(idx.begin(), idx.end(),
		[&v](size_t i1, size_t i2)
		{
			return v[i1] < v[i2];
		});

	return idx;
}

Statistics::Statistics(const std::vector<Measurement>& measurements)
{
	auto indices = sort_indices(measurements);
	_median = measurements[indices[measurements.size() / 2]];
	_min = measurements[indices[0]];
	_max = measurements[indices[measurements.size() - 1]];

	auto AddMeasurements = [](Measurement::Value a, const Measurement& b)
	{
		return a + b.GetValue();
	};

	Measurement::Value sum_values = std::accumulate(measurements.begin(), measurements.end(), _min->GetValue(), AddMeasurements);
	_mean = sum_values / measurements.size();

	auto SubMeanMeasurements = [&](const Measurement& x)
	{
		return x.GetValue() - _mean;
	};

	std::vector<Measurement::Value> diff(measurements.size(), _min->GetValue());
	std::transform(measurements.begin(), measurements.end(), diff.begin(), SubMeanMeasurements);

	auto sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), _min->GetValue());
	auto variance = sq_sum / measurements.size();

	_stddev = 100.0 * sqrt(variance) / _mean;
}

const Measurement& Statistics::Min() const
{
	return *_min;
}

const Measurement& Statistics::Max() const
{
	return *_max;
}

const Measurement& Statistics::Median() const
{
	return *_median;
}

const Measurement::Value& Statistics::Mean() const
{
	return _mean;
}

double Statistics::StdDev() const
{
	return _stddev;
}
