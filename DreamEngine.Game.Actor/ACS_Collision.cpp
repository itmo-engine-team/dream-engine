#include "ACS_Collision.h"

ACS_Collision::ACS_Collision(Actor* actor, Transform* transform, Vector2 size)
    : ActorComponentScene(actor, transform), size(size)
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
