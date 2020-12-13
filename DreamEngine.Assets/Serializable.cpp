#include "Serializable.h"

#include "ErrorLogger.h"

void Serializable::log(const std::string message)
{
    ErrorLogger::Log(Warning, message);
}
