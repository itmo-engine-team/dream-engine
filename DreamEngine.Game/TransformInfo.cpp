#include "TransformInfo.h"

TransformInfo::TransformInfo() : position(Vector3::Zero)
{

}

Vector3 TransformInfo::GetPosition() const
{
    return position;
}

void TransformInfo::SetPosition(Vector3 pos)
{
    position = pos;
}

Transform* TransformInfo::CreateTransform() const
{
    return new Transform(position);
}
