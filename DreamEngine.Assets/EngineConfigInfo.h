#pragma once

#include "Serializable.h"

class EngineConfigInfo : public Serializable
{

public:

    Json toJson() override;
    void fromJson(Json json) override;
    bool IsGameMode();

    int GetScreenWidth() const;
    int GetScreenHeight() const;

private:

    bool isGameMode = false;

    int screenWidth = 1200;
    int screenHeight = 800;

};