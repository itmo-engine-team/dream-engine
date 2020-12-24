#pragma once

#include "SimpleMath.h"
#include "Serializable.h"

using namespace DirectX::SimpleMath;

class SceneActorInfo;

class TransformInfo : Serializable
{

public:

    TransformInfo();
    TransformInfo(Vector3 pos);

    Vector3 GetPosition() const;
    void SetPosition(Vector3 pos);

protected:

    friend class SceneActorInfo;

    Json toJson() override;
    void fromJson(Json json) override;

private:

    Vector3 position;

};

