#pragma once

#include "Serializable.h"

class EngineConfigInfo : public Serializable
{

public:

    Json ToJson() override;
    void FromJson(Json json) override;
    bool IsGameMode();

private:

    bool isGameMode = false;
};