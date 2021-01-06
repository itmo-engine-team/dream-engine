#include "DeltaTimeHandler.h"

#include <algorithm>

float DeltaTimeHandler::GetDeltaTime() const
{
    return deltaTime * multiplier;
}

void DeltaTimeHandler::SetParentDeltaTime(const float deltaTime)
{
    this->deltaTime = deltaTime;
}

float DeltaTimeHandler::GetMultiplier() const
{
    return multiplier;
}

void DeltaTimeHandler::SetMultiplier(const float multiplier)
{
    this->multiplier = std::clamp(multiplier, 0.0f, 1.0f);
}
