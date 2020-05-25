#include "Compiler.hpp"

#include "Macro.hpp"
#include "String.hpp"

const char* Compiler::Name()
{
#if (COMPILER == COMPILER_MSVC)
	return "MSVC";
#elif (COMPILER == COMPILER_GCC)
	return "GCC";
#elif (COMPILER == COMPILER_CLANG)
	return "CLANG";
#else
	return "UNKNOWN";
#endif
}

const char* Compiler::Version()
{
#if (COMPILER == COMPILER_MSVC)
	static const int major = ((_MSC_VER / 100) - 5);
	static const int minor = (_MSC_VER % 100);
#elif (COMPILER & COMPILER_GCC)
	static const int major = (__GNUC__);
	static const int minor = (__GNUC_MINOR__);
#elif (COMPILER & COMPILER_CLANG)
	static const int major = (__clang_major__);
	static const int minor = (__clang_minor__);
#else
	static const int major = 0;
	static const int minor = 0;
#endif
	static const std::string version = ToString(major) + "." + ToString(minor);
	return version.c_str();
}
