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

void SceneRoom::AddActor(Actor* actor)
{
    actors.push_back(actor);
}

const std::vector<Actor*>& SceneRoom::GetActors() const
{
    return actors;
}
