#include "Scene.h"

#include "SceneAssetInfo.h"
#include "SceneRoomInfo.h"
#include "ActorContext.h"

Scene::Scene(ActorContext* context, SceneAssetInfo* sceneInfo) : context(context), sceneInfo(sceneInfo)
{
    for (SceneRoomInfo* roomInfo : sceneInfo->GetRoomInfoList())
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

SceneRoom* Scene::CreateNewRoom()
{
    SceneRoomInfo* roomInfo = new SceneRoomInfo();
    roomInfo->SetName("Room " + std::to_string(rooms.size()));
    sceneInfo->AddRoomInfo(roomInfo);

    SceneRoom* room = new SceneRoom(context, roomInfo);
    rooms.push_back(room);
    return room;
}

SceneRoom* Scene::GetCurrentRoom() const
{
    return currentRoom;
}

std::vector<SceneRoom*> Scene::GetRoomList() const
{
    return rooms;
}
