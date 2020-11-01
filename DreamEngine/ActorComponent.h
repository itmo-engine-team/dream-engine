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
    void DrawShadowMap();
    void RenderDeferred();

protected:

    Game* game;
    Actor* actor;

    virtual void onInit();
    virtual void onUpdate();
    virtual void onDraw();
    virtual void onDrawShadowMap();
    virtual void onRenderDeferred();
};

