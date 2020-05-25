#include "BenchmarkOptions.hpp"

BenchmarkOptions::BenchmarkOptions(CommandLine& commandLine)
    : help(commandLine.AddOption<BoolOption>("help", false)),
      iterations(commandLine.AddOption<ValueOption<int>>("iterations", 1)),
      filterMode(commandLine.AddOption<EnumOption<TestCase::Mode>>("mode", TestCase::Mode::All, std::set<TestCase::Mode>{ TestCase::Mode::All, TestCase::Mode::Disabled, TestCase::Mode::Nightly, TestCase::Mode::PreCommit })),
      filterName(commandLine.AddOption<ValueOption<std::string>>("filter", ".*")),
      filterId(commandLine.AddOption<ValueOption<std::string>>("range", "...")),
      cooldown(commandLine.AddOption<ValueOption<std::chrono::seconds>>("cooldown", std::chrono::seconds(0))),
      listTests(commandLine.AddOption<BoolOption>("list", false)),
      stopOnError(commandLine.AddOption<BoolOption>("stop-error", false)),
      throwError(commandLine.AddOption<BoolOption>("throw-error", false))
{
    help->SetDescription("Show this help message");
    iterations->SetDescription("Number of iterations per test case");
    filterMode->SetDescription("For managed datasets select which group to use");
    filterName->SetDescription("Regular expression to select test cases");
    filterId->SetDescription("List of test ids. '...' can be used to define a range");
    cooldown->SetDescription("Delay to add between test executions in seconds");
    listTests->SetDescription("List all test names");
    stopOnError->SetDescription("Abort execution after the first failed test");
    throwError->SetDescription("Don't catch fatal errors");
}
