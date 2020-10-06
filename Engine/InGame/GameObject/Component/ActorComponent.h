#pragma once

class Engine;
class Actor;

class ActorComponent
{

public:

    ActorComponent(Engine* engine, Actor* actor);
    virtual ~ActorComponent() = default;

    void Init();
    void Update();
    void Draw();

protected:

    Engine* engine;
    Actor* actor;

    virtual void onInit();
    virtual void onUpdate();
    virtual void onDraw();

};

