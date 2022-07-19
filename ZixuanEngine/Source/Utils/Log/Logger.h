#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <unordered_map>

/**
 * Zixuan Engine's global logging macro. Prints a message to the console
 * @param category		The category to log the message. See Logger::m_category and constructor for more info
 * @param format ...	The args to log
 */
#define ZE_LOG(category, format, ...)\
	ZE::Logger::Get().LogInfo(#category, __LINE__, __FILE__, format, __VA_ARGS__); 

namespace ZE
{
class ZE_API  Logger
{
public:
	enum class Color : int
	{
		kBlack = 0,
		kBlue = 1,
		kGreen = 2,
		kCyan = 3,
		kRed = 4,
		kMagenta = 5,
		kBrown = 6,
		kLightGray = 7,
		kDarkGray = 8,
		kLightBlue = 9,
		kLightGreen = 10,
		kLightCyan = 11,
		kLightRed = 12,
		kLightMagenta = 13,
		kYellow = 14,
		kWhite = 15,
		kBlueBackground = 63,
		kRedBackground = BACKGROUND_RED,

		kNum = 16
	};

private:
	HANDLE m_consoleHandle;
	Color m_currentColor;
	std::unordered_map<std::string, Color> m_category;     // map for log categories

public:
	static Logger& Get();

	void SetColor(Color color);
	void LogInfo(const std::string& category, int line, const char* file, const char* format, ...);
	template<typename Type>	void PrintInColor(Color color, const Type& message);
	template<typename Type>	void Print(const Type& message);
	template<typename Type>	void PrintLine(const Type& message);

private:
	Logger();
};

//-----------------------------------------------------------------------------------------------------------
// Immediately set color back to current after printed message
//-----------------------------------------------------------------------------------------------------------
template<typename Type>
inline void Logger::PrintInColor(Color color, const Type& message)
{
	SetConsoleTextAttribute(m_consoleHandle, static_cast<int>(color));
	std::cout << message;
	SetConsoleTextAttribute(m_consoleHandle, static_cast<int>(m_currentColor));
}

template<typename Type>
inline void Logger::Print(const Type& message)
{
	std::cout << message;
}

template<typename Type>
inline void Logger::PrintLine(const Type& message)
{
	std::cout << message << '\n';
}

}