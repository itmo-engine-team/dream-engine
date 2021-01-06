#pragma once

class GameObject
{
public:

    GameObject() = default;
    virtual ~GameObject() = default;

    virtual void Init();

protected:

    virtual void onInit();

};

