#pragma once

#include <vector>
#include "SceneRoom.h"

class SceneAssetInfo;
class SceneActorInfo;

class Scene
{

public:

    Scene(ActorContext* context, SceneAssetInfo* sceneInfo);
    ~Scene();

    SceneAssetInfo* GetSceneAssetInfo() const;
    
    //SceneRoom* CreateNewRoom();
    //SceneRoom* GetCurrentRoom() const;
    //std::vector<SceneRoom*> GetRoomList() const;

    SceneActorInfo* CreateActor();
    const std::vector<Actor*>& GetActors() const;

protected:

    ActorContext* context;
    SceneAssetInfo* sceneInfo;

    //SceneRoom* currentRoom;
    std::vector<SceneRoom*> rooms;

    std::vector<Actor*> actors;

};

