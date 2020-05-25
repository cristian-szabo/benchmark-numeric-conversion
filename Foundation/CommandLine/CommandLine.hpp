#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>

class Option;

class CommandLine final
{
public:

	template <typename T, typename... As>
	T* AddOption(const std::string& name, As&&... args);

	template <typename T, typename... As>
	T* AddPositionalOption(As&&... args);

	void Parse(int argc, char** argv);

	bool Validate() const;

	void PrintHelp() const;

private:

	using OptionsMap = std::map<std::string, std::unique_ptr<Option>>;

	using PositionalOptionsVector = std::vector<std::unique_ptr<Option>>;

	std::string _programName;

	OptionsMap _options{};

	PositionalOptionsVector  _positionalOptions{};

	std::vector<std::string> _unknownOptions{};

	std::vector<std::string> _invalidOptions{};

};

#include "CommandLine.inl"
