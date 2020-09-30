#include "GameObject.h"

GameObject::GameObject(Engine* engine) : engine(engine)
{

}

void GameObject::Init()
{
    onInit();
    // Call event AfterInit
}

void GameObject::onInit()
{

}
