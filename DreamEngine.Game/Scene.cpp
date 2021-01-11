#include "Scene.h"

#include "SceneAssetInfo.h"
#include "SceneRoomInfo.h"
#include "ActorContext.h"
#include "ActorFactory.h"

Scene::Scene(ActorContext* context, SceneAssetInfo* sceneInfo) : context(context), sceneInfo(sceneInfo)
{
    // Check if scene room is new
    if (sceneInfo == nullptr) return;

    for (SceneActorInfo* const actorInfo : sceneInfo->GetActorInfoList())
    {
        actors.push_back(ActorFactory::Create(context, actorInfo->GetType(), actorInfo->GetTransformInfo()));
    }

   /* for (SceneRoomInfo* roomInfo : sceneInfo->GetRoomInfoList())
    {
        rooms.push_back(new SceneRoom(context, roomInfo));
    }

    currentRoom = rooms.empty() ? nullptr : rooms[0];*/
}

Scene::~Scene()
{
    for (Actor* actor : actors)
    {
        delete actor;
    }

    /*for (SceneRoom* room : rooms)
    {
        delete room;
    }*/
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

void Scene::CreateActor()
{
    SceneActorInfo* actorInfo = new SceneActorInfo(ActorType::Actor);
    actorInfo->SetName("Actor " + std::to_string(actors.size()));
    sceneInfo->AddActorInfo(actorInfo);

    Actor* actor = ActorFactory::Create(context, actorInfo->GetType(), actorInfo->GetTransformInfo());
    actors.push_back(actor);
}

const std::vector<Actor*>& Scene::GetActors() const
{
    return actors;
}
