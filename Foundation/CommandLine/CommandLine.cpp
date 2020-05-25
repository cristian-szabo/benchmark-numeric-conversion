#include "CommandLine.hpp"

#include <iostream>
#include <regex>

#include "Option.hpp"

void CommandLine::Parse(int argc, char** argv)
{
    _programName = argv[0];

    const std::regex optionRegex{ "--((?:no-)?)([^=]+)(?:=(.*))?" };

    const auto SetOption = [&](const std::string& option, const std::string& name, const std::string& value)
    {
        if (_options.find(name) == _options.end())
        {
            _unknownOptions.push_back(option);
            return;
        }

        const bool success = _options[name]->Parse(value);

        if (!success)
        {
            _invalidOptions.push_back(option);
        }
    };

    unsigned int positionalIndex = 0;

    for (int i = 1; i < argc; ++i)
    {
        std::string mixed_case_opt{ argv[i] };
        int         equal_sign = mixed_case_opt.find('=');
        int         pos = (equal_sign == -1) ? strlen(argv[i]) : equal_sign;

        std::string option = mixed_case_opt.substr(0, pos);
        
        std::transform(option.begin(), option.end(), option.begin(), 
            [](std::string::value_type c) { return std::tolower(c); });
        
        option += mixed_case_opt.substr(pos);
        
        std::smatch optionMatches;

        if (std::regex_match(option, optionMatches, optionRegex))
        {
            if (optionMatches.str(3).empty())
            {
                SetOption(option, optionMatches.str(2), optionMatches.str(1).empty() ? "true" : "false");
            }
            else
            {
                if (!optionMatches.str(1).empty())
                {
                    _invalidOptions.emplace_back(option);
                }
                else
                {
                    SetOption(option, optionMatches.str(2), optionMatches.str(3));
                }
            }
        }
        else
        {
            if (positionalIndex >= _positionalOptions.size())
            {
                _invalidOptions.push_back(mixed_case_opt);
            }
            else
            {
                _positionalOptions[positionalIndex]->Parse(mixed_case_opt);
                ++positionalIndex;
            }
        }
    }
}

bool CommandLine::Validate() const
{
    bool isValid = true;

    for (auto& option : _options)
    {
        if (option.second->IsRequired() && !option.second->IsDefined())
        {
            isValid = false;
            std::cerr << "ERROR: Option '" << option.second->GetName() << "' is required but not given!\n";
        }
    }

    for (const auto& option : _positionalOptions)
    {
        if (option->IsRequired() && !option->IsDefined())
        {
            isValid = false;
            std::cerr << "ERROR: Option '" << option->GetName() << "' is required but not given!\n";
        }
    }

    for (const auto& option : _unknownOptions)
    {
        std::cerr << "WARNING: Skipping unknown option '" << option << "'!\n";
    }

    for (const auto& option : _invalidOptions)
    {
        std::cerr << "WARNING: Skipping invalid option '" << option << "'!\n";
    }

    return isValid;
}

void CommandLine::PrintHelp() const
{
    std::cout << "Usage: " << _programName << " \n";

    for (auto& option : _options)
    {
        std::cout << option.second->Help() << "\n";
    }

    for (const auto& option : _positionalOptions)
    {
        std::string displayHelp;

        const std::string messageHelp = option->Help();
        const size_t helpStartPos = messageHelp.find(" - ");

        if (helpStartPos != std::string::npos)
        {
            displayHelp = messageHelp.substr(helpStartPos);
        }

        std::cout << option->GetName() << displayHelp << "\n";
    }
}
