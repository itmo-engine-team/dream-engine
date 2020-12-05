#include "EngineConfigInfo.h"

Json EngineConfigInfo::ToJson()
{
    Json json = Serializable::ToJson();

    json["isGameMode"] = isGameMode;
    json["screenWidth"] = screenWidth;
    json["screenHeight"] = screenHeight;

    return json;
}

void EngineConfigInfo::FromJson(Json json)
{
    isGameMode = json["isGameMode"].get<bool>();
    screenWidth = json["screenWidth"].get<int>();
    screenHeight = json["screenHeight"].get<int>();
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
