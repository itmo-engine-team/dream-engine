#include "BTEditorNodeComposite.h"
#include "MapUtils.h"

BTEditorNodeComposite::BTEditorNodeComposite() : BTEditorNode(BTNodeType::Composite)
{
    SetCompositeType(BTNodeCompositeType::Selector);
}

BTNodeCompositeType BTEditorNodeComposite::GetCompositeType() const
{
    return compositeType;
}

void BTEditorNodeComposite::SetCompositeType(BTNodeCompositeType compositeType)
{
    this->compositeType = compositeType;
    setTypeName(MapUtils::TryGetByKey<BTNodeCompositeType, std::string>(
        MAP_NODE_COMPOSITE_TYPE_TO_STRING, compositeType, "UNKNOWN"));
}

bool BTEditorNodeComposite::CanHaveParent()
{
    return true;
}

bool BTEditorNodeComposite::CanHaveChild()
{
    return true;
}

bool BTEditorNodeComposite::CanHaveChildren()
{
    return true;
}

Json BTEditorNodeComposite::toJson()
{
    Json json = BTEditorNode::toJson();

    json["compositeType"] = MapUtils::TryGetByKey<BTNodeCompositeType, std::string>(
        MAP_NODE_COMPOSITE_TYPE_TO_STRING, compositeType, "UNKNOWN");

    return json;
}

void BTEditorNodeComposite::fromJson(Json json)
{
    BTEditorNode::fromJson(json);

    std::string stringType = json["compositeType"];
    compositeType = MapUtils::TryGetByValue<BTNodeCompositeType, std::string>(
        MAP_NODE_COMPOSITE_TYPE_TO_STRING, stringType, BTNodeCompositeType::Selector);
}
