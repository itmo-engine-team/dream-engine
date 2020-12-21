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

protected:

    std::vector<Actor*> actors;

};

