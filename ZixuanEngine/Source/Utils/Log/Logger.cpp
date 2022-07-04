#include "Logger.h"

namespace ZE
{
Logger& Logger::Get()
{
	static Logger s_instance;
	return s_instance;
}

void Logger::SetColor(Color color)
{
	SetConsoleTextAttribute(m_consoleHandle, static_cast<int>(color));
}

void Logger::LogInfo(const std::string& category, int line, const char* file, const char* format, ...)
{
	char messageBuffer[512];

	va_list args;
	va_start(args, format);

	vsprintf_s(messageBuffer, format, args);

	va_end(args);

	// Truncate fully-qualified path
	std::string fullPath = file;
	fullPath = fullPath.substr(fullPath.find_last_of('\\') + 1);

	// Get timestamp
	time_t clock = time(nullptr);
	std::tm now;
	localtime_s(&now, &clock);	// Converts given time since epoch
	const std::string time = std::to_string(now.tm_hour) + ":" + std::to_string(now.tm_min) + ((now.tm_hour >= 12) ? " PM" : " AM");

	// Log the message
	SetColor(m_category[category]);
	std::cout << "[" << category << "]" << fullPath << "(" << line << ") - " << messageBuffer << ". Time: " << time << std::endl;
}

Logger::Logger()
	: m_consoleHandle{ GetStdHandle(STD_OUTPUT_HANDLE) }
	, m_currentColor{ Color::kLightGray }
{
	m_category.insert({ "Info", Color::kLightGray });
	m_category.insert({ "Error", Color::kRed });
	m_category.insert({ "Warning", Color::kYellow });
	m_category.insert({ "Prompt", Color::kCyan });
}
}