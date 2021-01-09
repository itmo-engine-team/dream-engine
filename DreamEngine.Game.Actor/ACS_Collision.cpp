#include "ACS_Collision.h"

ACS_Collision::ACS_Collision(Actor* actor, Vector2 size) : ActorComponentScene(actor), size(size)
{
}

Vector2 ACS_Collision::GetSize()
{
    return size;
}

void ACS_Collision::SetSize(Vector2 newSize)
{
    size = newSize;
}
