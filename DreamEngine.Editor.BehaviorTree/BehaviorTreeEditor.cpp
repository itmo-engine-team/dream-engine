#include "BehaviorTreeEditor.h"

BehaviorTreeEditor::BehaviorTreeEditor() : lastId(0)
{
}

int BehaviorTreeEditor::GenerateNewId()
{
    lastId++;
    return lastId;
}

Json BehaviorTreeEditor::toJson()
{
    Json json = Serializable::toJson();

    json["lastId"] = lastId;

    return json;
}

void BehaviorTreeEditor::fromJson(Json json)
{
    initVariable(json, "lastId", &lastId);
}
