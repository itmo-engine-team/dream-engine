#define _CRT_SECURE_NO_WARNINGS

#include "ErrorLogger.h"

#include <ctime>


void ErrorLogger::Log(LogType type, std::string message)
{
	std::string errorMessage = GetDate();
	switch (type)
	{
	case Error:
		errorMessage += "\nERROR: ";
		break;
	case Warning:
		errorMessage += "\nWARNING: ";
		break;
	case Info:
		errorMessage += "\nINFO: ";
		break;
	}	
	errorMessage += message;

	std::ofstream logFile;
	
	logFile.open("Log\\log.txt", std::ios::app);

	if (logFile.is_open() == true)
	{
		logFile << "\n" << errorMessage << "\n" << std::endl;
		logFile.close();
	}
	printf(errorMessage.c_str());
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
		errorMessage += "\nWARNING: ";
		break;
	case Error:
		errorMessage += "\nERROR: ";
		break;
	case Info:
		errorMessage += "\nINFO: ";
		break;
	}
		
	errorMessage += std::string(msg);
	errorMessage += "\nFile: " + file;
	errorMessage += "\nFunction: " + function + " [" + std::to_string(line) + "] ";

	if (logFile.is_open() == true)
	{
		logFile << "\n" << errorMessage << "\n" <<std::endl;
		logFile.close();
	}
	
	switch (type)
	{
	case Error:
		printf(errorMessage.c_str());
		//MessageBoxA(GetActiveWindow(), error_message.c_str(), "Error", MB_ICONERROR);
		exit(0);
	default:
		printf(errorMessage.c_str());
	}
	
	printf(errorMessage.c_str());

}

char* ErrorLogger::GetDate()
{
	// current date/time based on current system
	time_t now = time(0);
	// convert now to string form
	char* dt = ctime(&now);

	return dt;
}
