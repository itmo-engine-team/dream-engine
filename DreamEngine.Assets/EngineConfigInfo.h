#pragma once

#include "Serializable.h"

class EngineConfigInfo : public Serializable
{

public:

    inline static const std::string ENGINE_VERSION = "1.1";

    Json toJson() override;
    void fromJson(Json json) override;
    bool IsGameMode();

    int GetScreenWidth() const;
    int GetScreenHeight() const;

private:

    bool isGameMode = false;

    int screenWidth = 1600;
    int screenHeight = 900;

};