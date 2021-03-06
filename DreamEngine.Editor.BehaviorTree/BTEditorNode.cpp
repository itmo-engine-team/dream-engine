#include "BTEditorNode.h"

#include "MapUtils.h"
#include "ErrorLogger.h"
#include "BTEditorNodeFactory.h"

BTEditorNode::BTEditorNode(BTNodeType type)
    : type(type), id(-1), name(""), typeName("Abstract"), position(ImVec2(0, 0))
{
    parentLink = std::pair(-1, nullptr);
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

void BTEditorNode::setId(int id)
{
    this->id = id;
}

const std::string& BTEditorNode::GetName() const
{
    return name;
}

const std::string& BTEditorNode::GetTypeName() const
{
    return typeName;
}

void BTEditorNode::SetName(const std::string& name)
{
    this->name = name;
}

void BTEditorNode::setTypeName(const std::string& name)
{
    typeName = name;
}

const ImVec2& BTEditorNode::GetPosition() const
{
    return position;
}

BTNodeType BTEditorNode::GetType() const
{
    return type;
}

void BTEditorNode::SetPosition(ImVec2 position)
{
    this->position = position;
}

bool BTEditorNode::HasParent() const
{
    return parentLink.second != nullptr;
}

int BTEditorNode::GetParentAttributeId() const
{
    return parentAttributeId;
}

void BTEditorNode::setParentAttributeId(int attributeId)
{
    parentAttributeId = attributeId;
}

std::pair<int, BTEditorNode*> BTEditorNode::GetParentLink() const
{
    return parentLink;
}

bool BTEditorNode::HasAnyChild()
{
    return !childrenLinks.empty();
}

void BTEditorNode::setParentLink(std::pair<int, BTEditorNode*> parentLink)
{
    this->parentLink = parentLink;
}

void BTEditorNode::removeParent()
{
    parentLink = std::pair(-1, nullptr);
}

int BTEditorNode::GetChildrenAttributeId() const
{
    return childrenAttributeId;
}

void BTEditorNode::setChildrenAttributeId(int attributeId)
{
    childrenAttributeId = attributeId;
}

void BTEditorNode::removeChild(BTEditorNode* child, bool removeChildParent)
{
    for (auto iter = childrenLinks.begin(); iter < childrenLinks.end(); ++iter)
    {
        if (iter->second == child)
        {
            if (removeChildParent) iter->second->removeParent();
            childrenLinks.erase(iter);
            return;
        }
    }
}

void BTEditorNode::removeChildren(bool removeChildParent)
{
    if (removeChildParent)
    {
        for (auto childLink : childrenLinks)
        {
            childLink.second->removeParent();
        }
    }

    childrenLinks.clear();
}

const std::vector<std::pair<int, BTEditorNode*>>& BTEditorNode::GetChildrenLinks() const
{
    return childrenLinks;
}

void BTEditorNode::addChildLink(std::pair<int, BTEditorNode*> child)
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

    if (CanHaveParent())
    {
        json["parentAttributeId"] = parentAttributeId;
    }

    if (!CanHaveChild())
        return json;

    json["childrenAttributeId"] = childrenAttributeId;

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

    if (CanHaveParent())
        initVariable(json, "parentAttributeId", &parentAttributeId);

    if (!CanHaveChild())
        return;

    initVariable(json, "childrenAttributeId", &childrenAttributeId);

    // Create children
    if (!json.contains("children"))
        return;

    Json childrenJsonArray = json["children"];
    for (Json childLinkJson : childrenJsonArray)
    {
        const Json childJson = childLinkJson[1];
        initVariable(childJson, "type", &stringType);
        auto childType = MapUtils::TryGetByValue<BTNodeType, std::string>(MAP_NODE_TYPE_TO_STRING, stringType, BTNodeType::UNKNOWN);
        BTEditorNode* child = BTEditorNodeFactory::Create(childType);

        if (child == nullptr)
        {
            ErrorLogger::Log(Error, "BTEditorNode child can't be created: " + stringType + "/n" + json.dump());
            continue;
        }

        child->fromJson(childJson);
        childrenLinks.push_back(std::pair(childLinkJson[0].get<int>(), child));
        child->setParentLink(std::pair(childLinkJson[0].get<int>(), this));
    }
}
