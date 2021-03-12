#pragma once
/*
* SHDebug
* Debug output class
* @TODO:
* Log Message Function
*	Output given
* Output to a log file
* Draw functions
*/

#include <SDL_log.h>

namespace DebugHelper
{
	constexpr auto IsDebug()
	{
#ifdef DEBUG
		return true;
#else
		return false;
#endif
	}
}

class SHDebug
{
// Singleton implementation
	// Scott Meyers Effective Modern C++ better error message if the deleted functions are in public
	static SHDebug& getInstance()
	{
		static SHDebug instance;
		return instance;
	}

	SHDebug(SHDebug const&) = delete;
	void operator=(SHDebug const&) = delete;

private:
	SHDebug() {}

	// Rest of declarations ahead
public:

	// Log message
	template<typename T, typename...Ts>
	constexpr void LogMessage(int type, T head, Ts... tail);

	// Log error
	template<typename T, typename...Ts>
	constexpr void LogError(int channel, T head, Ts... tail);

	// Output to file

	// Draw functions?

public:
	// Extended categories
	// See SDL_log.h categories
	enum
	{
		MY_LOG_CUSTOM_CATEGORY = SDL_LOG_CATEGORY_CUSTOM
	} SH_LogCategory;
};

template<typename T, typename ...Ts>
inline constexpr void SHDebug::LogMessage(int channel, T head, Ts ...tail)
{
	if constexpr (DebugHelper::IsDebug())
	{
		SDL_LogVerbose(channel, T, Ts);
	}
}

template <typename T, typename ... Ts>
constexpr void SHDebug::LogError(int channel, T head, Ts... tail)
{
}
