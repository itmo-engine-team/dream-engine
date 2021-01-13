#pragma once

#include <vector>
#include "SceneRoom.h"

class Game;
class ActorAssetInfo;
class SceneAssetInfo;
class SceneActorInfo;

class Scene
{

public:

    Scene(Game* game, ActorContext* context, SceneAssetInfo* sceneInfo);
    ~Scene();

    SceneAssetInfo* GetSceneAssetInfo() const;
    
    //SceneRoom* CreateNewRoom();
    //SceneRoom* GetCurrentRoom() const;
    //std::vector<SceneRoom*> GetRoomList() const;

    SceneActorInfo* CreateNewActorInfo();
    void CreateActorOnScene(SceneActorInfo* actorInfo);
    void DeleteActorFromScene(SceneActorInfo* actorInfo);
    Actor* CreateActorFromAsset(ActorAssetInfo* actorAssetInfo);

    void UpdateCameraTransform();

protected:

    Game* game;
    ActorContext* context;
    SceneAssetInfo* sceneInfo;

    //SceneRoom* currentRoom;
    std::vector<SceneRoom*> rooms;

};

