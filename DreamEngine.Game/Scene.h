#pragma once

#include <vector>
#include "SceneRoom.h"

class SceneAssetInfo;

class Scene
{

public:

    Scene(ActorContext* context, SceneAssetInfo* sceneInfo);
    ~Scene();

    SceneAssetInfo* GetSceneAssetInfo() const;

    SceneRoom* GetCurrentRoom() const;
    std::vector<SceneRoom*> GetRoomList() const;

protected:

    SceneAssetInfo* sceneInfo;

    SceneRoom* currentRoom;
    std::vector<SceneRoom*> rooms;

};

