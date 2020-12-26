#include "Scene.h"

#include "SceneAssetInfo.h"
#include "ActorContext.h"

Scene::Scene(ActorContext* context, SceneAssetInfo* sceneInfo) : sceneInfo(sceneInfo)
{
    for (SceneRoomInfo* roomInfo: sceneInfo->GetRoomInfoList())
    {
        rooms.push_back(new SceneRoom(context, roomInfo));
    }

    currentRoom = rooms.empty() ? nullptr : rooms[0];
}

Scene::~Scene()
{
    for (SceneRoom* room : rooms)
    {
        delete room;
    }
}

SceneAssetInfo* Scene::GetSceneAssetInfo() const
{
    return sceneInfo;
}

SceneRoom* Scene::GetCurrentRoom() const
{
    return currentRoom;
}

std::vector<SceneRoom*> Scene::GetRoomList() const
{
    return rooms;
}
