#include "TestFilter.hpp"

#include <sstream>
#include <string>

#include "TestContext.hpp"

TestFilter::TestFilter(TestCase::Mode mode, std::string nameFilter, std::string idFilter)
    : _mode{ mode }, _nameFilter{ nameFilter }, _idFilter{ ParseIdFilter(idFilter) }
{}

bool TestFilter::SkipTestCase(const TestInfo &info) const
{
    const bool includeDisabled = (info.mode == _mode) && (_mode == TestCase::Mode::Disabled);
    
    if (info.mode == TestCase::Mode::Disabled && !includeDisabled)
    {
        return true;
    }

    if (!std::regex_search(info.name, _nameFilter))
    {
        return true;
    }

    if (!_idFilter.empty())
    {
        bool found = false;

        for (auto& range : _idFilter)
        {
            if (range.first <= info.id && info.id <= range.second)
            {
                found = true;
                break;
            }
        }

        if(!found)
        {
            return true;
        }
    }

    return false;
}

TestFilter::Ranges TestFilter::ParseIdFilter(const std::string &idFilter) const
{
    Ranges ranges;
    std::string str;
    bool inRange = false;
    int value = 0;
    int start = 0;
    int end = std::numeric_limits<int>::max();

    std::stringstream stream(idFilter);

    std::getline(stream, str, ',');

    if (stream.fail())
    {
        return ranges;
    }

    if (str.find("...") != std::string::npos)
    {
        inRange = true;
    }
    else
    {
        start = std::stoi(str);
        end = start;
    }

    while (!stream.eof())
    {
        std::getline(stream, str, ',');

        if (stream.fail())
        {
            break;
        }

        if (str.find("...") != std::string::npos)
        {
            inRange = true;
            end = std::numeric_limits<int>::max();
        }
        else
        {
            value = std::stoi(str);

            if (inRange || end == value - 1)
            {
                end = value;
                inRange = false;
            }
            else
            {
                ranges.emplace_back(start, end);
                start = value;
                end = start;
            }
        }
    }

    ranges.emplace_back(start, end);

    return ranges;
}
