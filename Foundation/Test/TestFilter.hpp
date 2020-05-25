#pragma once

#include <regex>
#include <utility>
#include <vector>

#include "TestCase.hpp"

struct TestInfo;

class TestFilter final
{
public:

    TestFilter(TestCase::Mode mode, std::string nameFilter, std::string idFilter);

    bool SkipTestCase(const TestInfo &info) const;

private:

    using Ranges = std::vector<std::pair<int, int>>;

    TestCase::Mode _mode{ TestCase::Mode::All };

    std::regex _nameFilter{ ".*" };

    Ranges _idFilter{};

    Ranges ParseIdFilter(const std::string& idFilter) const;

};
