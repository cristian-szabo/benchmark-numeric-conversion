#pragma once

#include "Datasets/ItemDataset.hpp"

const auto DatasetSmallIterations = MakeItem("Iterations", 1000000);
const auto DatasetMediumIterations = MakeItem("Iterations", 10000000);
const auto DatasetLargeIterations = MakeItem("Iterations", 100000000);
