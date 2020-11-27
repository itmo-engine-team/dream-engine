#pragma once

#include <Windows.h>
#include <fstream>

enum LogType
{
	Warning,
	Error,
	Info
};


class ErrorLogger
{
public:
	
	static void Log(LogType type, std::string message);
	static void DirectXLog(HRESULT hr, LogType type, const std::string& msg, const std::string& file, const std::string& function, int line);
	
private:
	
	static char* GetDate();
};