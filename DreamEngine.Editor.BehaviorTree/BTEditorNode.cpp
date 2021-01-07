#include "BTEditorNode.h"

#include "MapUtils.h"
#include "ErrorLogger.h"
#include "BTEditorNodeFactory.h"

BTEditorNode::BTEditorNode(BTNodeType type)
    : type(type), id(-1), name(""), position(ImVec2(0, 0))
{
    parentLink = std::pair(0, nullptr);
}

BTEditorNode::~BTEditorNode()
{
    for (auto childLink : childrenLinks)
    {
        delete childLink.second;
    }
}

int BTEditorNode::GetId() const
{
    return id;
}

void BTEditorNode::SetId(int id)
{
    this->id = id;
}

const std::string& BTEditorNode::GetName() const
{
    return name;
}

void BTEditorNode::SetName(const std::string& name)
{
    this->name = name;
}

std::pair<int, BTEditorNode*> BTEditorNode::GetParentLink() const
{
    return parentLink;
}

void BTEditorNode::SetParentLink(std::pair<int, BTEditorNode*> parentLink)
{
    this->parentLink = parentLink;
}

const std::vector<std::pair<int, BTEditorNode*>>& BTEditorNode::GetChildrenLinks() const
{
    return childrenLinks;
}

void BTEditorNode::AddChildLink(std::pair<int, BTEditorNode*> child)
{
    childrenLinks.push_back(child);
}

Json BTEditorNode::toJson()
{
    Json json = Serializable::toJson();

    json["id"] = id;
    json["type"] = MapUtils::TryGetByKey<BTNodeType, std::string>(MAP_NODE_TYPE_TO_STRING, type, "UNKNOWN");
    json["name"] = name;
    json["position"] = { position.x, position.y };
    json["parentLinkId"] = parentLink.first;

    // Create children
    if (childrenLinks.empty())
        return json;

    Json childrenJsonArray = Json::array();
    for (std::pair<int, BTEditorNode*> childLink : childrenLinks)
    {
        childrenJsonArray.push_back({ childLink.first, childLink.second->toJson() });
    }
    json["children"] = childrenJsonArray;

    return json;
}

void BTEditorNode::fromJson(Json json)
{
    initVariable(json, "id", &id);

    std::string stringType;
    initVariable(json, "type", &stringType);
    type = MapUtils::TryGetByValue<BTNodeType, std::string>(MAP_NODE_TYPE_TO_STRING, stringType, BTNodeType::UNKNOWN);
    if (type == BTNodeType::UNKNOWN)
        ErrorLogger::Log(Error, "BTEditorNode has invalid type: " + stringType + "/n" + json.dump());

    initVariable(json, "name", &name);

    Json posJsonArray = json["position"];
    position = ImVec2(posJsonArray[0], posJsonArray[1]);

    // Create children
    if (!json.contains("children"))
        return;

    Json childrenJsonArray = json["children"];
    for (Json childLinkJson : childrenJsonArray)
    {
        const Json childJson = childLinkJson[1];
        initVariable(json, "type", &stringType);
        type = MapUtils::TryGetByValue<BTNodeType, std::string>(MAP_NODE_TYPE_TO_STRING, stringType, BTNodeType::UNKNOWN);
        BTEditorNode* child = BTEditorNodeFactory::Create(type);

        if (child == nullptr)
        {
            ErrorLogger::Log(Error, "BTEditorNode child can't be created: " + stringType + "/n" + json.dump());
            continue;
        }

        child->fromJson(childJson);
        childrenLinks.push_back(std::pair(childLinkJson[0].get<int>(), child));
        child->SetParentLink(std::pair(childJson["parentLinkId"].get<int>(), this));
    }
}
