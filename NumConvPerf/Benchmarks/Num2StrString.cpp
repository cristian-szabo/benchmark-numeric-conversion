#include "Test.hpp"

#include "Fixtures/Num2StrStringFixture.hpp"
#include "Datasets/NumberDatasets.hpp"
#include "Datasets/IterationDatasets.hpp"
#include "Datasets/CartesianProductDataset.hpp"

TEST_SUITE_BEGIN(Performance)
TEST_SUITE_BEGIN(Num2Str)
TEST_SUITE_BEGIN(String)

REGISTER_FIXTURE_DATA_TEST_CASE(U8, Num2StrStringFixture<uint8_t>, TestCase::Mode::All, Combine(DatasetNumberU8, DatasetSmallIterations))
REGISTER_FIXTURE_DATA_TEST_CASE(S8, Num2StrStringFixture<int8_t>, TestCase::Mode::All, Combine(DatasetNumberS8, DatasetSmallIterations))
REGISTER_FIXTURE_DATA_TEST_CASE(U16, Num2StrStringFixture<uint16_t>, TestCase::Mode::All, Combine(DatasetNumberU16, DatasetSmallIterations))
REGISTER_FIXTURE_DATA_TEST_CASE(S16, Num2StrStringFixture<int16_t>, TestCase::Mode::All, Combine(DatasetNumberS16, DatasetSmallIterations))
REGISTER_FIXTURE_DATA_TEST_CASE(U32, Num2StrStringFixture<uint32_t>, TestCase::Mode::All, Combine(DatasetNumberU32, DatasetSmallIterations))
REGISTER_FIXTURE_DATA_TEST_CASE(S32, Num2StrStringFixture<int32_t>, TestCase::Mode::All, Combine(DatasetNumberS32, DatasetSmallIterations))
REGISTER_FIXTURE_DATA_TEST_CASE(U64, Num2StrStringFixture<uint64_t>, TestCase::Mode::All, Combine(DatasetNumberU64, DatasetSmallIterations))
REGISTER_FIXTURE_DATA_TEST_CASE(S64, Num2StrStringFixture<int64_t>, TestCase::Mode::All, Combine(DatasetNumberS64, DatasetSmallIterations))
REGISTER_FIXTURE_DATA_TEST_CASE(F32, Num2StrStringFixture<float>, TestCase::Mode::All, Combine(DatasetNumberF32, DatasetSmallIterations))
REGISTER_FIXTURE_DATA_TEST_CASE(F64, Num2StrStringFixture<double>, TestCase::Mode::All, Combine(DatasetNumberF64, DatasetSmallIterations))

TEST_SUITE_END()
TEST_SUITE_END()
TEST_SUITE_END()
