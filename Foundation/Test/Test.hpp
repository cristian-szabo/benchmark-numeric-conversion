#pragma once

#include "Macro.hpp"

#include "TestCase.hpp"
#include "TestRegister.hpp"

/*
	Test Suite Register
*/

#define TEST_SUITE(NAME) \
namespace NAME##Suite { static TestSuiteRegister NAME##SuiteRegister{ #NAME }; }

#define TEST_SUITE_BEGIN(NAME) \
namespace NAME##Suite { static TestSuiteRegister NAME##SuiteRegisterBegin{ #NAME };

#define TEST_SUITE_END() \
static TestSuiteRegister SuiteRegisterEnd; }

/*
	Test Case Register
*/

#define TEST_CASE_REGISTER(NAME, MODE, STATUS) \
static TestCaseRegister<NAME> NAME##Register { #NAME, MODE, STATUS }

/*
    Test Case Class Member Functions
*/

#define TEST_CASE_CONSTRUCTOR(NAME) \
NAME() = default;

/*
    Test Case Class
*/

#define TEST_CASE_CLASS(NAME, MODE, STATUS) \
class NAME : public TestCase \
{ \
public: \
    TEST_CASE_CONSTRUCTOR(NAME) \
    void Run() override; \
}; \
TEST_CASE_REGISTER(NAME, MODE, STATUS); \
void NAME::Run()

/*
    Test Case Mode
*/

#define TEST_CASE(NAME, MODE) \
    TEST_CASE_CLASS(NAME, MODE, TestCase::Status::Active)
#define EXPECTED_FAILURE_TEST_CASE(NAME, MODE) \
    TEST_CASE_CLASS(NAME, MODE, TestCase::Status::ExpectedFailure)
#define DISABLED_TEST_CASE(NAME, MODE) \
    TEST_CASE_CLASS(NAME, MODE, TestCase::Status::Disabled)

/*
    Data Test Case Register
*/

#define DATA_TEST_CASE_REGISTER(NAME, MODE, STATUS, DATASET) \
static TestCaseRegister<NAME<decltype(DATASET)::Type>> NAME##Register { #NAME, MODE, STATUS, DATASET };

/*
    Test Case Class Member Functions
*/

#define DATA_TEST_CASE_CONSTRUCTOR(NAME) \
template <typename D> \
explicit NAME(D&& data) : DataTestCase{ std::move(data) } \
{}

/*
    Data Test Case Class
*/

#define DATA_TEST_CASE_CLASS(NAME, MODE, STATUS, DATASET, ...)                                                  \
template <typename T>                                                                                           \
class NAME;                                                                                                \
template <typename... As>                                                                                       \
class NAME<std::tuple<As...>> : public DataTestCase<decltype(DATASET)::Type>                                  \
{                                                                                                               \
public:                                                                                                     \
    DATA_TEST_CASE_CONSTRUCTOR(NAME)                                                              \
    void Run() override                                                                                      \
    {                                                                                                           \
        std::apply(this, &NAME::run<As...>, GetData());                                                         \
    }                                                                                                   \
private:                                                                                                        \
    template <MAKE_TYPE_PARAMS(__VA_ARGS__)>                                                                    \
    void Run(MAKE_ARG_PARAMS(__VA_ARGS__));                                                                     \
};                                                                                                              \
DATA_TEST_CASE_REGISTER(NAME, MODE, STATUS, DATASET);                                                          \
template <typename... As>                                                                                       \
template <MAKE_TYPE_PARAMS(__VA_ARGS__)>                                                                        \
void NAME<std::tuple<As...>>::Run(MAKE_ARG_PARAMS(__VA_ARGS__))

/*
    Data Test Case Mode
*/

#define DATA_TEST_CASE(NAME, MODE, DATASET, ...) \
    DATA_TEST_CASE_CLASS(NAME, MODE, TestCase::Status::Active, DATASET, __VA_ARGS__)
#define EXPECTED_FAILURE_DATA_TEST_CASE(NAME, MODE, DATASET, ...) \
    DATA_TEST_CASE_CLASS(NAME, MODE, TestCase::Status::ExpectedFailure, DATASET, __VA_ARGS__)
#define DISABLED_DATA_TEST_CASE(NAME, MODE, DATASET, ...) \
    DATA_TEST_CASE_CLASS(NAME, MODE, TestCase::Status::Disabled, DATASET, __VA_ARGS__)

/*
    Test Fixture Member Functions
*/

#define FIXTURE_SETUP(NAME) \
void Setup() override { NAME::Setup(); }

#define FIXTURE_DATA_SETUP(NAME) \
void Setup() override { std::apply(&NAME::Setup<As...>, std::tuple_cat(std::make_tuple(this), GetData())); }

#define FIXTURE_RUN(NAME) \
void Run() override { NAME::Run(); }

#define FIXTURE_SYNC(NAME) \
void Sync() override { NAME::Sync(); }

#define FIXTURE_TEARDOWN(NAME) \
void Teardown() override { NAME::Teardown(); }

/*
    Fixture Test Case Class
*/

#define FIXTURE_TEST_CASE_CLASS(NAME, FIXTURE, MODE, STATUS)                    \
class NAME : public TestCase, public FIXTURE \
{                                                                               \
public:                                                                     \
    TEST_CASE_CONSTRUCTOR(NAME)                                            \
    FIXTURE_SETUP(FIXTURE)                                                      \
    void Run() override;                                                     \
    FIXTURE_TEARDOWN(FIXTURE)                                                   \
};                                                                              \
TEST_CASE_REGISTER(NAME, MODE, STATUS);                                        \
void NAME::Run()

/*
    Fixture Test Case Mode
*/

#define FIXTURE_TEST_CASE(NAME, FIXTURE, MODE) \
    FIXTURE_TEST_CASE_CLASS(NAME, FIXTURE, MODE, TestCase::Status::Active)
#define EXPECTED_FAILURE_FIXTURE_TEST_CASE(NAME, FIXTURE, MODE) \
    FIXTURE_TEST_CASE_CLASS(NAME, FIXTURE, MODE, TestCase::Status::ExpectedFailure)
#define DISABLED_FIXTURE_TEST_CASE(NAME, FIXTURE, MODE) \
    FIXTURE_TEST_CASE_CLASS(NAME, FIXTURE, MODE, TestCase::Status::Disabled)

/*
    Fixture Data Test Case Class
*/

#define FIXTURE_DATA_TEST_CASE_CLASS(NAME, FIXTURE, MODE, STATUS, DATASET)                                                      \
template <typename T>                                                                                                           \
class NAME;                                                                                                                \
template <typename... As>                                                                                                       \
class NAME<std::tuple<As...>> : public DataTestCase<decltype(DATASET)::Type>, public FIXTURE \
{                                                                                                                               \
public:                                                                                                                     \
    DATA_TEST_CASE_CONSTRUCTOR(NAME, DATASET)                                                                              \
    FIXTURE_DATA_SETUP(FIXTURE)                                                                                                 \
    void Run() override;                                                                                                     \
    FIXTURE_TEARDOWN(FIXTURE)                                                                                                   \
};                                                                                                                              \
DATA_TEST_CASE_REGISTER(NAME, MODE, STATUS, DATASET);                                                                          \
template <typename... As>                                                                                                       \
void NAME<std::tuple<As...>>::Run()

/*
    Fixture Data Test Case Mode
*/

#define FIXTURE_DATA_TEST_CASE(NAME, FIXTURE, MODE, DATASET) \
    FIXTURE_DATA_TEST_CASE_CLASS(NAME, FIXTURE, MODE, TestCase::Status::Active, DATASET)
#define EXPECTED_FAILURE_FIXTURE_DATA_TEST_CASE(NAME, FIXTURE, MODE, DATASET) \
    FIXTURE_DATA_TEST_CASE_CLASS(NAME, FIXTURE, MODE, TestCase::Status::ExpectedFailure, DATASET)
#define DISABLED_FIXTURE_DATA_TEST_CASE(NAME, FIXTURE, MODE, DATASET) \
    FIXTURE_DATA_TEST_CASE_CLASS(NAME, FIXTURE, MODE, TestCase::Status::Disabled, DATASET)

/*
    Register Fixture Test Case Class
*/

#define REGISTER_FIXTURE_TEST_CASE_CLASS(NAME, FIXTURE, MODE, STATUS)           \
class NAME : public TestCase, public FIXTURE                                    \
{                                                                               \
public:                                                                         \
    TEST_CASE_CONSTRUCTOR(NAME)                                                 \
    FIXTURE_SETUP(FIXTURE)                                                      \
    FIXTURE_RUN(FIXTURE)                                                        \
    FIXTURE_SYNC(FIXTURE)                                                       \
    FIXTURE_TEARDOWN(FIXTURE)                                                   \
};                                                                              \
TEST_CASE_REGISTER(NAME, MODE, STATUS)

/*
    Register Fixture Test Case Mode
*/

#define REGISTER_FIXTURE_TEST_CASE(NAME, FIXTURE, MODE) \
    REGISTER_FIXTURE_TEST_CASE_CLASS(NAME, FIXTURE, MODE, TestCase::Status::Active)
#define EXPECTED_FAILURE_REGISTER_FIXTURE_TEST_CASE(NAME, FIXTURE, MODE) \
    REGISTER_FIXTURE_TEST_CASE_CLASS(NAME, FIXTURE, MODE, TestCase::Status::ExpectedFailure)
#define DISABLED_REGISTER_FIXTURE_TEST_CASE(NAME, FIXTURE, MODE) \
    REGISTER_FIXTURE_TEST_CASE_CLASS(NAME, FIXTURE, MODE, TestCase::Status::Disabled)

/*
    Register Fixture Data Test Case Class
*/

#define REGISTER_FIXTURE_DATA_TEST_CASE_CLASS(NAME, FIXTURE, MODE, STATUS, DATASET)                                             \
template <typename T>                                                                                                           \
class NAME;                                                                                                                     \
template <typename... As>                                                                                                       \
class NAME<std::tuple<As...>> : public DataTestCase<decltype(DATASET)::Type>, public FIXTURE                                    \
{                                                                                                                               \
public:                                                                                                                         \
    DATA_TEST_CASE_CONSTRUCTOR(NAME)                                                                                            \
    FIXTURE_DATA_SETUP(FIXTURE)                                                                                                 \
    FIXTURE_RUN(FIXTURE)                                                                                                        \
    FIXTURE_SYNC(FIXTURE)                                                                                                       \
    FIXTURE_TEARDOWN(FIXTURE)                                                                                                   \
};                                                                                                                              \
DATA_TEST_CASE_REGISTER(NAME, MODE, STATUS, DATASET)                                                                        

/*
    Register Fixture Data Test Case Mode
*/

#define REGISTER_FIXTURE_DATA_TEST_CASE(NAME, FIXTURE, MODE, DATASET) \
    REGISTER_FIXTURE_DATA_TEST_CASE_CLASS(NAME, FIXTURE, MODE, TestCase::Status::Active, DATASET)
#define EXPECTED_FAILURE_REGISTER_FIXTURE_DATA_TEST_CASE(NAME, FIXTURE, MODE, DATASET) \
    REGISTER_FIXTURE_DATA_TEST_CASE_CLASS(NAME, FIXTURE, MODE, TestCase::Status::ExpectedFailure, DATASET)
#define DISABLED_REGISTER_FIXTURE_DATA_TEST_CASE(NAME, FIXTURE, MODE, DATASET) \
    REGISTER_FIXTURE_DATA_TEST_CASE_CLASS(NAME, FIXTURE, MODE, TestCase::Status::Disabled, DATASET)
