#pragma once
#pragma once
#include <Windows.h>
#include "StringConverter.h"
#include <fstream>

class ErrorLogger
{
public:
	static void Log(std::string message);
	static void DirectXError(HRESULT hr, const std::string& msg, const std::string& file, const std::string& function, int line);
	static void DirectXWarning(HRESULT hr, const std::string& msg, const std::string& file, const std::string& function, int line);
};