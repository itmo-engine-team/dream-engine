#pragma once

#include <vector>
#include "SceneRoom.h"

class ActorAssetInfo;
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

    SceneActorInfo* CreateNewActorInfo();
    void CreateActorOnScene(SceneActorInfo* actorInfo);
    void DeleteActorFromScene(SceneActorInfo* actorInfo);
    Actor* CreateActorFromAsset(ActorAssetInfo* actorAssetInfo);

    const std::vector<Actor*>& GetActors() const;

protected:

    ActorContext* context;
    SceneAssetInfo* sceneInfo;

    //SceneRoom* currentRoom;
    std::vector<SceneRoom*> rooms;

    std::vector<Actor*> actors;

};

