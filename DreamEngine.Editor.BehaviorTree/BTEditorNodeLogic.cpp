#include "BTEditorNodeLogic.h"
#include "MapUtils.h"
#include "ErrorLogger.h"

BTEditorNodeLogic::BTEditorNodeLogic() : BTEditorNode(BTNodeType::Logic)
{
    setTypeName("Logic");
    SetLogicType(BTNodeLogicType::MoveTo);
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

BTNodeLogicType BTEditorNodeLogic::GetLogicType() const
{
    return logicType;
}

void BTEditorNodeLogic::SetLogicType(BTNodeLogicType logicType)
{
    this->logicType = logicType;
    setTypeName(MapUtils::TryGetByKey<BTNodeLogicType, std::string>(
        MAP_NODE_LOGIC_TYPE_TO_STRING, logicType, "UNKNOWN"));
}

Json BTEditorNodeLogic::toJson()
{
    Json json = BTEditorNode::toJson();

    json["logicType"] = MapUtils::TryGetByKey<BTNodeLogicType, std::string>(
        MAP_NODE_LOGIC_TYPE_TO_STRING, logicType, "UNKNOWN");

    return json;
}

void BTEditorNodeLogic::fromJson(Json json)
{
    BTEditorNode::fromJson(json);

    std::string stringType;
    initVariable(json, "logicType", &stringType);
    setTypeName(stringType);

    logicType = MapUtils::TryGetByValue<BTNodeLogicType, std::string>(
        MAP_NODE_LOGIC_TYPE_TO_STRING, stringType, BTNodeLogicType::UNKNOWN);
    if (logicType == BTNodeLogicType::UNKNOWN)
        ErrorLogger::Log(Error, "Logic type has invalid type: " + stringType + "/n" + json.dump());
}
