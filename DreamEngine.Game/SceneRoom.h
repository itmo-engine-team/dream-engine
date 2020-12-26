#pragma once

#include <vector>
#include <string>

class SceneRoomInfo;
class Actor;
class ActorContext;

class SceneRoom
{

public:

    SceneRoom(ActorContext* context, SceneRoomInfo* roomInfo);
    ~SceneRoom();

    SceneRoomInfo* GetRoomInfo() const;

    const std::string& GetName() const;
    void SetName(const std::string& name);

    void AddActor(Actor* actor);
    const std::vector<Actor*>& GetActors() const;

protected:

    SceneRoomInfo* roomInfo;

    std::string name;
    std::vector<Actor*> actors;

};

