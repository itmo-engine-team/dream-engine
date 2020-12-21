#pragma once

#include <vector>

class Game;
class SceneRoomInfo;
class Actor;

class SceneRoom
{

public:

    SceneRoom(Game* game, SceneRoomInfo* roomInfo);
    ~SceneRoom();

    void AddActor(Actor* actor);

    const std::vector<Actor*>& GetActors() const;

protected:

    std::vector<Actor*> actors;

};

