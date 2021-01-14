#pragma once

#include "Serializable.h"

class EngineConfigInfo : public Serializable
{

public:

    inline static const std::string ENGINE_VERSION = "2.11";

    Json toJson() override;
    void fromJson(Json json) override;
    bool IsGameMode() const;
    unsigned int GetStartSceneId() const;

    int GetScreenWidth() const;
    int GetScreenHeight() const;

private:

    bool isGameMode = false;
    unsigned int startSceneId = 0;

    int screenWidth = 1600;
    int screenHeight = 900;

};