#include "ErrorLogger.h"


void ErrorLogger::Log(std::string message)
{
	std::string error_message = "Error: " + message;
	std::ofstream logFile;

	logFile.open("Log\\log.txt", std::ios::app);

	if (logFile.is_open() == true)
	{
		logFile << "\n" << error_message << std::endl;
		logFile.close();
	};
}

void ErrorLogger::DirectXError(HRESULT hr, const std::string& msg, const std::string& file, const std::string& function, int line)
{
	if (FAILED(hr))
	{
		std::ofstream logFile;
		logFile.open("Log\\log.txt", std::ios::app);

		std::string error_message;

		error_message = "Msg: " + std::string(msg);
		error_message += "\nFile: " + file;
		error_message += "\nFunction: " + function;
		error_message += "\nLine: " + std::to_string(line);

		MessageBoxW(NULL, StringConverter::StringToWide(error_message).c_str(), L"Error", MB_ICONERROR);
		if (logFile.is_open() == true)
		{
			logFile << "\n" << error_message << std::endl;
			logFile.close();
		};

		exit(0);
	}

}

void ErrorLogger::DirectXWarning(HRESULT hr, const std::string& msg, const std::string& file, const std::string& function, int line)
{
	if (FAILED(hr))
	{
		std::ofstream logFile;
		logFile.open("Log\\log.txt", std::ios::app);

		std::string error_message;

		error_message = "Msg: " + std::string(msg);
		error_message += "\nFile: " + file;
		error_message += "\nFunction: " + function;
		error_message += "\nLine: " + std::to_string(line);

		MessageBoxW(NULL, StringConverter::StringToWide(error_message).c_str(), L"Warning", MB_ICONWARNING);
		if (logFile.is_open() == true)
		{
			logFile << "\n" << error_message << std::endl;
			logFile.close();
		}

	}
}
