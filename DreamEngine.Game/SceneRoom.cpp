#include "SceneRoom.h"

#include "Actor.h"
#include "SceneRoomInfo.h"
#include "ActorFactory.h"

SceneRoom::SceneRoom(ActorContext* context, SceneRoomInfo* roomInfo) : context(context), roomInfo(roomInfo)
{
    // Check if scene room is new
    if (roomInfo == nullptr) return;

    for (SceneActorInfo* const actorInfo : roomInfo->GetActorInfoList())
    {
        actors.push_back(ActorFactory::Create(context, actorInfo));
    }
}

SceneRoom::~SceneRoom()
{
    for (Actor* actor : actors)
    {
        delete actor;
    }
}

SceneRoomInfo* SceneRoom::GetRoomInfo() const
{
    return roomInfo;
}

void SceneRoom::CreateActor()
{
    SceneActorInfo* actorInfo = new SceneActorInfo(ActorType::Actor);
    actorInfo->SetName("Actor " + std::to_string(actors.size()));
    roomInfo->AddActorInfo(actorInfo);

    Actor* actor = ActorFactory::Create(context, actorInfo);
    actors.push_back(actor);
}

const std::vector<Actor*>& SceneRoom::GetActors() const
{
    return actors;
}
