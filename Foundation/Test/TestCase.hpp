#pragma once

#include <istream>
#include <ostream>

class TestCase
{
public:

    enum class Status
    {
        Active,
        ExpectedFailure,
        Disabled
    };

    enum class Mode
    {
        All,
        Disabled,
        PreCommit,
        Nightly
    };

    virtual ~TestCase() = default;

    virtual void Setup();

    virtual void Run();

    virtual void Sync();

    virtual void Teardown();

};

template <typename T>
class DataTestCase : public TestCase
{
public:

    explicit DataTestCase(T data);

    const T& GetData() const;

private:

    T _data;

};

std::istream& operator>>(std::istream& is, TestCase::Mode& mode);

std::istream& operator>>(std::istream& is, TestCase::Status& status);

std::ostream& operator<<(std::ostream& os, TestCase::Mode mode);

std::ostream& operator<<(std::ostream& os, TestCase::Status status);

#include "TestCase.inl"
