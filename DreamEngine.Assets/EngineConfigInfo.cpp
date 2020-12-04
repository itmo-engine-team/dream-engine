#include "EngineConfigInfo.h"

void EngineConfigInfo::FromJson(Json json)
{
    isGameMode = json["isGameMode"].get<bool>();
}

bool EngineConfigInfo::IsGameMode()
{
    return isGameMode;
}

Json EngineConfigInfo::ToJson()
{
    Json json = Serializable::ToJson();
    json["isGameMode"] = isGameMode;
    return json;
}
