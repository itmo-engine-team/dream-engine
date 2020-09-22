#include "GameObject.h"

GameObject::GameObject(Game* game) : game(game)
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
