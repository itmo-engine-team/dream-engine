#pragma once

class Engine;

class GameObject
{
public:

    GameObject(Engine* engine);
    virtual ~GameObject() = default;

    void Init();

protected:

    Engine* engine;

    virtual void onInit();

};

