#include "EngineConfigInfo.h"

Json EngineConfigInfo::toJson()
{
    Json json = Serializable::toJson();

    json["isGameMode"] = isGameMode;
    json["startSceneId"] = startSceneId;
    json["screenWidth"] = screenWidth;
    json["screenHeight"] = screenHeight;

    return json;
}

void EngineConfigInfo::fromJson(Json json)
{
    initVariable(json, "isGameMode", &isGameMode);
    initVariable(json, "startSceneId", &startSceneId);
    initVariable(json, "screenWidth", &screenWidth);
    initVariable(json, "screenHeight", &screenHeight);
}

bool EngineConfigInfo::IsGameMode() const
{
    return isGameMode;
}

unsigned int EngineConfigInfo::GetStartSceneId() const
{
    return startSceneId;
}

int EngineConfigInfo::GetScreenWidth() const
{
    return screenWidth;
}

int EngineConfigInfo::GetScreenHeight() const
{
    return screenHeight;
}
