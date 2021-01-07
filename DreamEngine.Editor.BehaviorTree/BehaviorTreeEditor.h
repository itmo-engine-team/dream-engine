#pragma once

#include "Serializable.h"

class BehaviorTreeEditor : Serializable
{

public:

    BehaviorTreeEditor();

    int GenerateNewId();

    Json toJson() override;
    void fromJson(Json json) override;

private:

    int lastId;

};

