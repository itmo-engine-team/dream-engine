#define _CRT_SECURE_NO_WARNINGS
#include "ErrorLogger.h"
#include <ctime>


void ErrorLogger::Log(LogType type, std::string message)
{
	std::string error_message = GetDate();
	switch (type)
	{
	case Error:
		error_message += "\nError: ";
		break;
	case Warning:
		error_message += "\nWarning: ";
		break;
	}	
	error_message += message;

	std::ofstream logFile;
	
	logFile.open("Log\\log.txt", std::ios::app);

	if (logFile.is_open() == true)
	{
		logFile << "\n" << error_message << std::endl;
		logFile.close();
	}
}

void ErrorLogger::DirectXLog(HRESULT hr, LogType type, const std::string& msg, const std::string& file, const std::string& function, int line)
{
	
	if (FAILED(hr))
	{
		
		std::ofstream logFile;
		logFile.open("Log\\log.txt", std::ios::app);

		std::string error_message;

		error_message = GetDate();

		switch (type)
		{
		case Warning:
			error_message += "Warning: ";
			break;
		case Error:
			error_message += "Error: ";
			break;
		}
		
		error_message += std::string(msg);
		error_message += "\nFile: " + file;
		error_message += "\nFunction: " + function;
		error_message += "\nLine: " + std::to_string(line);

		if (logFile.is_open() == true)
		{
			logFile << "\n" << error_message << std::endl;
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

}

char* ErrorLogger::GetDate()
{
	// current date/time based on current system
	time_t now = time(0);
	// convert now to string form
	char* dt = ctime(&now);

	return dt;
}
