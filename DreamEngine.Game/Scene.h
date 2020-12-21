#pragma once

#include <vector>
#include "SceneRoom.h"

class Game;
class SceneAssetInfo;

class Scene
{

public:

    Scene(Game* game, SceneAssetInfo* sceneInfo);
    ~Scene();

protected:

    SceneRoom* currentRoom;
    std::vector<SceneRoom*> rooms;

};

