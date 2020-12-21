#include "BaseSceneViewer.h"

#include <algorithm>

BaseSceneViewer::BaseSceneViewer()
{
}

InputSystem* BaseSceneViewer::GetInputSystem() const
{
    return inputSystem;
}

Graphics* BaseSceneViewer::GetGraphics() const
{
    return graphics;
}

void BaseSceneViewer::Init(InputSystem* inputSystem, Graphics* graphics)
{
    this->inputSystem = inputSystem;
    this->graphics = graphics;
}

void BaseSceneViewer::Update(const float engineDeltaTime)
{
    this->engineDeltaTime = engineDeltaTime;
}

void BaseSceneViewer::SetDeltaTimeMultiplier(float deltaTimeMultiplier)
{
    deltaTimeMultiplier = std::clamp(deltaTimeMultiplier, 0.0f, 1.0f);
}

float BaseSceneViewer::GetDeltaTimeMultiplier()
{
    return deltaTimeMultiplier;
}

float BaseSceneViewer::GetDeltaTime()
{
    return engineDeltaTime * deltaTimeMultiplier;
}

