#pragma once

#include <vector>
#include "SceneRoom.h"

class SceneAssetInfo;

class Scene
{

public:

    Scene(ActorContext* context, SceneAssetInfo* sceneInfo);
    ~Scene();

    SceneRoom* GetCurrentRoom() const;

protected:

    SceneRoom* currentRoom;
    std::vector<SceneRoom*> rooms;

};

