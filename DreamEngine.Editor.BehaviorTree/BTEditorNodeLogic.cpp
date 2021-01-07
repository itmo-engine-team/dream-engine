#include "BTEditorNodeLogic.h"

BTEditorNodeLogic::BTEditorNodeLogic() : BTEditorNode(BTNodeType::Logic)
{
}

bool BTEditorNodeLogic::CanHaveParent()
{
    return true;
}

bool BTEditorNodeLogic::CanHaveChild()
{
    return false;
}

bool BTEditorNodeLogic::CanHaveChildren()
{
    return false;
}

Json BTEditorNodeLogic::toJson()
{
    Json json = BTEditorNode::toJson();

    return json;
}

void BTEditorNodeLogic::fromJson(Json json)
{
    BTEditorNode::fromJson(json);
    
}
