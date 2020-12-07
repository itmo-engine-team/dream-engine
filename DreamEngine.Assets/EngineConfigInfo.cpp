#include "EngineConfigInfo.h"

Json EngineConfigInfo::toJson()
{
    Json json = Serializable::toJson();

    json["isGameMode"] = isGameMode;
    json["screenWidth"] = screenWidth;
    json["screenHeight"] = screenHeight;

    return json;
}

void EngineConfigInfo::fromJson(Json json)
{
    initVariable(json, "isGameMode", &isGameMode);
    initVariable(json, "screenWidth", &screenWidth);
    initVariable(json, "screenHeight", &screenHeight);
}

bool EngineConfigInfo::IsGameMode()
{
    return isGameMode;
}

int EngineConfigInfo::GetScreenWidth() const
{
    return screenWidth;
}

int EngineConfigInfo::GetScreenHeight() const
{
    return screenHeight;
}
