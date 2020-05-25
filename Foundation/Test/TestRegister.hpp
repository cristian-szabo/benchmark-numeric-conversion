#pragma once

#include <string>

#include "TestCase.hpp"

class TestSuiteRegister final
{
public:

    TestSuiteRegister();

    TestSuiteRegister(std::string name);

};

template <typename T>
class TestCaseRegister final
{
public:

    TestCaseRegister(std::string name, TestCase::Mode mode, TestCase::Status status, std::string description = "");

    template <typename D>
    TestCaseRegister(std::string name, TestCase::Mode mode, TestCase::Status status, D&& dataset);

};

#include "TestRegister.inl"
