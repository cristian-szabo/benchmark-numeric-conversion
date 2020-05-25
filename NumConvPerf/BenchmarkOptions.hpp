#pragma once

#include <chrono>

#include "Options/ValueOption.hpp"
#include "Options/BoolOption.hpp"
#include "Options/EnumOption.hpp"
#include "CommandLine.hpp"

#include "TestFilter.hpp"

class BenchmarkOptions
{
public:

    BenchmarkOptions(CommandLine& commandLine);

    BoolOption* help{};

    ValueOption<int32_t>* iterations{};

    EnumOption<TestCase::Mode>* filterMode{};
    
    ValueOption<std::string>* filterName{};

    ValueOption<std::string>* filterId{};

    ValueOption<std::chrono::seconds>* cooldown{};

    BoolOption* listTests{};

    BoolOption* stopOnError{};

    BoolOption* throwError{};

};
