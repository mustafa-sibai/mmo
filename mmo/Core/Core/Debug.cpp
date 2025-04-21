#include "Debug.h"
#include <iostream>
#include <ctime>
#include <filesystem>

std::ofstream Debug::logFile;
std::string Debug::logFileName;
bool Debug::initialized = false;

void Debug::InitializeLogFile()
{
	if (logFile.is_open())
	{
		return; // Already initialized
	}

	// Ensure the logs directory exists
	const std::string logDirectory = "./logs/";
	std::filesystem::create_directories(logDirectory);

	// Generate log file name based on current date and time
	time_t now = time(nullptr);
	tm localTime;
	localtime_s(&localTime, &now);

	char buffer[64];
	strftime(buffer, sizeof(buffer), "log-%Y-%m-%d-%H-%M-%S.log", &localTime);
	logFileName = logDirectory + buffer;

	// Open the log file
	logFile.open(logFileName, std::ios::out | std::ios::app);
	if (!logFile.is_open())
	{
		std::cerr << "Failed to open log file: " << logFileName << std::endl;
	}
}

void Debug::LogInfo(const std::string& message)
{
	Log(message, "INFO", FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, std::cout);
}

void Debug::LogWarning(const std::string& message)
{
	Log(message, "WARNING", FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN, std::cout);
}

void Debug::LogError(const std::string& message)
{
	Log(message, "ERROR", FOREGROUND_INTENSITY | FOREGROUND_RED, std::cerr);
}

void Debug::Log(const std::string& message, const std::string& level, WORD color, std::ostream& outputStream)
{
	if (!initialized)
	{
		InitializeLogFile();
		initialized = true;
	}

	// Get current time
	time_t now = time(nullptr);
	tm localTime;
	localtime_s(&localTime, &now);

	char timeBuffer[32];
	strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", &localTime);

	// Log to console with color
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	outputStream << "[" << timeBuffer << "] [" << level << "] " << message << std::endl;
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset to default color

	// Log to file
	if (logFile.is_open())
	{
		logFile << "[" << timeBuffer << "] [" << level << "] " << message << std::endl;
	}
}