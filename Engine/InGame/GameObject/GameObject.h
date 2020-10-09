#pragma once

class Game;

class GameObject
{
public:

    GameObject(Game* game);
    virtual ~GameObject() = default;

    void Init();

protected:

    Game* game;

    virtual void onInit();

};

