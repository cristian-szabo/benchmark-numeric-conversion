#pragma once

#define COMPILER_UNKNOWN		0x00000000
#define COMPILER_MSVC			0x01000000
#define COMPILER_GCC			0x02000000
#define COMPILER_CLANG			0x20000000

// Clang
#if defined(__clang__)
#	define COMPILER COMPILER_CLANG

// Visual C++
#elif defined(_MSC_VER)
#	define COMPILER COMPILER_MSVC

// GCC
#elif defined(__GNUC__) || defined(__MINGW32__)
#	define COMPILER COMPILER_GCC
#else
#	define COMPILER COMPILER_UNKNOWN
#endif

#ifndef COMPILER
#	error "Compiler is unknown, your compiler may not be supported."
#endif

class Compiler
{
public:

	static const char* Name();

	static const char* Version();

};
