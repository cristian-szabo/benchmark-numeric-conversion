#include "Test.hpp"

#include "Fixtures/Str2NumScanFixture.hpp"
#include "Datasets/StringNumberDatasets.hpp"
#include "Datasets/IterationDatasets.hpp"
#include "Datasets/CartesianProductDataset.hpp"

TEST_SUITE_BEGIN(Performance)
TEST_SUITE_BEGIN(Str2Num)
TEST_SUITE_BEGIN(Scan)

REGISTER_FIXTURE_DATA_TEST_CASE(U8, Str2NumScanFixture<uint8_t>, TestCase::Mode::All, Combine(DatasetStringNumberU8, DatasetSmallIterations))
REGISTER_FIXTURE_DATA_TEST_CASE(S8, Str2NumScanFixture<int8_t>, TestCase::Mode::All, Combine(DatasetStringNumberS8, DatasetSmallIterations))
REGISTER_FIXTURE_DATA_TEST_CASE(U16, Str2NumScanFixture<uint16_t>, TestCase::Mode::All, Combine(DatasetStringNumberU16, DatasetSmallIterations))
REGISTER_FIXTURE_DATA_TEST_CASE(S16, Str2NumScanFixture<int16_t>, TestCase::Mode::All, Combine(DatasetStringNumberS16, DatasetSmallIterations))
REGISTER_FIXTURE_DATA_TEST_CASE(U32, Str2NumScanFixture<uint32_t>, TestCase::Mode::All, Combine(DatasetStringNumberU32, DatasetSmallIterations))
REGISTER_FIXTURE_DATA_TEST_CASE(S32, Str2NumScanFixture<int32_t>, TestCase::Mode::All, Combine(DatasetStringNumberS32, DatasetSmallIterations))
REGISTER_FIXTURE_DATA_TEST_CASE(U64, Str2NumScanFixture<uint64_t>, TestCase::Mode::All, Combine(DatasetStringNumberU64, DatasetSmallIterations))
REGISTER_FIXTURE_DATA_TEST_CASE(S64, Str2NumScanFixture<int64_t>, TestCase::Mode::All, Combine(DatasetStringNumberS64, DatasetSmallIterations))
REGISTER_FIXTURE_DATA_TEST_CASE(F32, Str2NumScanFixture<float>, TestCase::Mode::All, Combine(DatasetStringNumberF32, DatasetSmallIterations))
REGISTER_FIXTURE_DATA_TEST_CASE(F64, Str2NumScanFixture<double>, TestCase::Mode::All, Combine(DatasetStringNumberF64, DatasetSmallIterations))

TEST_SUITE_END()
TEST_SUITE_END()
TEST_SUITE_END()
