#pragma once

#include "Datasets/VectorDataset.hpp"

const auto DatasetNumberU8 = MakeVec<uint8_t>("Number", 0, 16, 128);
const auto DatasetNumberS8 = MakeVec<int8_t>("Number", -127, -16, -1);

const auto DatasetNumberU16 = MakeVec<uint16_t>("Number", 1024, 16384);
const auto DatasetNumberS16 = MakeVec<int16_t>("Number", -16383, -1024);

const auto DatasetNumberU32 = MakeVec<uint32_t>("Number", 131072U, 1048576U, 16777216U, 134217728U, 1073741824U);
const auto DatasetNumberS32 = MakeVec<int32_t>("Number", -1073741824, -134217728, -16777216, -1048576, -131072);

const auto DatasetNumberU64 = MakeVec<uint64_t>("Number", 17179869184UL, 1099511627776UL, 140737488355328UL, 18014398509481984UL, 1152921504606846976UL);
const auto DatasetNumberS64 = MakeVec<int64_t>("Number", -1152921504606846976L, -18014398509481984L, -140737488355328L, -1099511627776L, -17179869184L);

const auto DatasetNumberF32 = MakeVec<float>("Number", 1.123456F, 512.1234F, 1024.123F, 32768.12F, 131072.1F);
const auto DatasetNumberF64 = MakeVec<double>("Number", 1.1234567891011121, 2.123456789101112, 4096.123456789101, 262144.1234567891, 8388608.12345678);
