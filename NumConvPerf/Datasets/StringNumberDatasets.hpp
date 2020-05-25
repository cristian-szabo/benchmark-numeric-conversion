#pragma once

#include "Datasets/VectorDataset.hpp"

const auto DatasetStringNumberU8 = MakeVec("String", "0", "16", "128");
const auto DatasetStringNumberS8 = MakeVec("String", "-127", "-16", "-1");

const auto DatasetStringNumberU16 = MakeVec("String", "1024", "16384");
const auto DatasetStringNumberS16 = MakeVec("String", "-16383", "-1024");

const auto DatasetStringNumberU32 = MakeVec("String", "131072", "1048576", "16777216", "134217728", "1073741824");
const auto DatasetStringNumberS32 = MakeVec("String", "-1073741824", "-134217728", "-16777216", "-1048576", "-131072");

const auto DatasetStringNumberU64 = MakeVec("String", "17179869184", "1099511627776", "140737488355328", "18014398509481984", "1152921504606846976");
const auto DatasetStringNumberS64 = MakeVec("String", "-1152921504606846976", "-18014398509481984", "-140737488355328", "-1099511627776", "-17179869184");

const auto DatasetStringNumberF32 = MakeVec("String", "1.123456", "512.1234", "1024.123", "32768.12", "131072.1");
const auto DatasetStringNumberF64 = MakeVec("String", "1.1234567891011121", "2.123456789101112", "4096.123456789101", "262144.1234567891", "8388608.12345678");
