#pragma once

class Game;
class Actor;

class ActorComponent
{

public:

    ActorComponent(Game* game, Actor* actor);
    virtual ~ActorComponent() = default;

    void Init();
    void Update();
    void Draw();

protected:

    Game* game;
    Actor* actor;

    virtual void onInit();
    virtual void onUpdate();
    virtual void onDraw();

};

