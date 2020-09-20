#define _CRT_SECURE_NO_WARNINGS
#include "ErrorLogger.h"
#include <ctime>


void ErrorLogger::Log(LogType type, std::string message)
{
	std::string errorMessage = GetDate();
	switch (type)
	{
	case Error:
		errorMessage += "\nError: ";
		break;
	case Warning:
		errorMessage += "\nWarning: ";
		break;
	}	
	errorMessage += message;

	std::ofstream logFile;
	
	logFile.open("Log\\log.txt", std::ios::app);

	if (logFile.is_open() == true)
	{
		logFile << "\n" << errorMessage << std::endl;
		logFile.close();
	}
}

void ErrorLogger::DirectXLog(HRESULT hr, LogType type, const std::string& msg, const std::string& file, const std::string& function, int line)
{
	
	if (!FAILED(hr)) return;
		
	std::ofstream logFile;
	logFile.open("Log\\log.txt", std::ios::app);

	std::string errorMessage;

	errorMessage = GetDate();

	switch (type)
		{
		case Warning:
			errorMessage += "Warning: ";
			break;
		case Error:
			errorMessage += "Error: ";
			break;
		}
		
	errorMessage += std::string(msg);
	errorMessage += "\nFile: " + file;
	errorMessage += "\nFunction: " + function;
	errorMessage += "\nLine: " + std::to_string(line);

	if (logFile.is_open() == true)
	{
		logFile << "\n" << errorMessage << std::endl;
		logFile.close();
	}
	int msgboxID;
	switch (type)
	{
	case Error:
		
		//MessageBoxA(GetActiveWindow(), error_message.c_str(), "Error", MB_ICONERROR);
		exit(0);
	case Warning:
		break;
	}
		
	

}

char* ErrorLogger::GetDate()
{
	// current date/time based on current system
	time_t now = time(0);
	// convert now to string form
	char* dt = ctime(&now);

	return dt;
}
