#pragma once

#include "Serializer.h"

class EngineConfigInfo : public Serializer
{

public:

    EngineConfigInfo(bool isGameMode = false);

    json ToJson() override;   
    Serializer* FromJson(std::filesystem::path pathToConfig) override;

    bool isGameMode = false;
};