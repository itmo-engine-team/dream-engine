#include "GameObject.h"

GameObject::GameObject(ActorContext context) : context(context)
{

}

const ActorContext& GameObject::GetContext() const
{
    return context;
}

void GameObject::Init()
{
    onInit();
    // Call event AfterInit
}

void GameObject::onInit()
{

}
