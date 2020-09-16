#include "GameObject.h"

GameObject::GameObject(Game* game, Vector3 position) : m_game(game)
{
	transform = new Transform(position);
}