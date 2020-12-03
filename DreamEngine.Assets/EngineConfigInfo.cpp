#include "EngineConfigInfo.h"

EngineConfigInfo::EngineConfigInfo(bool isGameMode) : isGameMode(isGameMode)
{
}

Serializer* EngineConfigInfo::FromJson(std::filesystem::path pathToConfig)
{
    std::ifstream i(pathToConfig);
    json j;
    i >> j;

    isGameMode = j["isGameMode"].get<bool>();

    return this;
}

json EngineConfigInfo::ToJson()
{
   json j = json{ {"isGameMode", isGameMode}};
   return j;
}
