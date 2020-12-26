#include "SceneRoom.h"

#include "Actor.h"
#include "SceneRoomInfo.h"
#include "ActorFactory.h"

SceneRoom::SceneRoom(ActorContext* context, SceneRoomInfo* roomInfo) : roomInfo(roomInfo)
{
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

const std::string& SceneRoom::GetName() const
{
    return name;
}

void SceneRoom::SetName(const std::string& name)
{
    this->name = name;
}

void SceneRoom::AddActor(Actor* actor)
{
    actors.push_back(actor);
}

const std::vector<Actor*>& SceneRoom::GetActors() const
{
    return actors;
}
