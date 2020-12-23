#pragma once

class GameObject
{
public:

    GameObject();
    virtual ~GameObject() = default;

    virtual void Init();

protected:

    virtual void onInit();

};

