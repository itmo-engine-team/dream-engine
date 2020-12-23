#include "Scene.h"

#include "SceneAssetInfo.h"
#include "ActorContext.h"

Scene::Scene(ActorContext* context, SceneAssetInfo* sceneInfo)
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

SceneRoom* Scene::GetCurrentRoom() const
{
    return currentRoom;
}
