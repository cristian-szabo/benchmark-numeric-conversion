#include <iostream>

#include "Compiler.hpp"

#include "TestContext.hpp"
#include "BenchmarkOptions.hpp"

#include "CommandLine.hpp"

#include "Instruments/WallClock.hpp"

int main(int argc, char** argv)
{
	std::cout << "Compiled with: " << Compiler::Name() << "-" << Compiler::Version() << std::endl;

	CommandLine parser;

	BenchmarkOptions options(parser);
	parser.Parse(argc, argv);

	if (options.help->IsDefined() && options.help->GetValue())
	{
		parser.PrintHelp();
		return 0;
	}

	auto& context = TestContext::GetInstance();

	if (options.listTests->GetValue())
	{
		context.PrintTestInfo();
		return 0;
	}

	TestConfig config;
	config.filter = TestFilter{ options.filterMode->GetValue(), options.filterName->GetValue(), options.filterId->GetValue() };
	config.iterations = options.iterations->GetValue();
	config.cooldown = options.cooldown->GetValue();
	context.SetConfig(config);

	auto& profiler = context.GetProfiler();
	profiler.AddInstrument(std::make_unique<WallClock>(Instrument::ScaleFactor::TimeMS));

	bool success = false;

	try
	{
		success = context.Run();
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << "\n";

		if (options.throwError->GetValue())
		{
			throw ex;
		}
	}

	return (success ? 0 : 1);
}
