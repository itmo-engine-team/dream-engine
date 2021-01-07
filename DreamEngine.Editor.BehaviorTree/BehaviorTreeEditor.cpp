#include "BehaviorTreeEditor.h"

#include <queue>

#include "MapUtils.h"
#include "BTEditorNodeFactory.h"
#include "ErrorLogger.h"

BehaviorTreeEditor::BehaviorTreeEditor() : lastId(-1)
{
    rootNode = new BTEditorNodeRoot();
    fillNodeIds(rootNode);
}

BTEditorNode* BehaviorTreeEditor::CreateNode(BTNodeType type, ImVec2 position)
{
    BTEditorNode* node = BTEditorNodeFactory::Create(type);
    fillNodeIds(node);
    node->SetPosition(position);

    unparentedNodes.push_back(node);
    return node;
}

void BehaviorTreeEditor::CreateLink(int parentAttributeId, int childAttributeId)
{
    BTEditorNode* parentNode = findNodeByChildrenAttributeId(parentAttributeId);
    BTEditorNode* childNode = findNodeByParentAttributeId(childAttributeId);

    // Check if nodes were found
    if (parentNode == nullptr || childNode == nullptr)
        return;

    // Check if nodes can be linked
    if (!(parentNode->CanHaveChild() && childNode->CanHaveParent()))
        return;

    int linkId = generateNewId();
    parentNode->addChildLink(std::pair(linkId, childNode));
    childNode->setParentLink(std::pair(linkId, parentNode));
}

BTEditorNode* BehaviorTreeEditor::GetRootNode() const
{
    return rootNode;
}

const std::vector<BTEditorNode*>& BehaviorTreeEditor::GetUnparentedNodes() const
{
    return unparentedNodes;
}

int BehaviorTreeEditor::generateNewId()
{
    lastId++;
    return lastId;
}

void BehaviorTreeEditor::fillNodeIds(BTEditorNode* node)
{
    node->setId(generateNewId());

    if (node->CanHaveParent())
        node->setParentAttributeId(generateNewId());

    if (node->CanHaveChild())
        node->setChildrenAttributeId(generateNewId());
}

BTEditorNode* BehaviorTreeEditor::findNodeByParentAttributeId(int parentAttributeId)
{
    std::function<bool(BTEditorNode*, int)> checkFunction = [](BTEditorNode* node, int parentAttributeId)
    {
        return node->CanHaveParent() && node->GetParentAttributeId() == parentAttributeId;
    };

    return findNode(checkFunction, parentAttributeId);
}

BTEditorNode* BehaviorTreeEditor::findNodeByChildrenAttributeId(int childrenAttributeId)
{
    std::function<bool(BTEditorNode*, int)> checkFunction = [](BTEditorNode* node, int childrenAttributeId)
    {
        return node->CanHaveChild() && node->GetChildrenAttributeId() == childrenAttributeId;
    };

    return findNode(checkFunction, childrenAttributeId);
}

BTEditorNode* BehaviorTreeEditor::findNode(
    const std::function<bool(BTEditorNode*, int)>& checkFunction, int idToCheck)
{
    BTEditorNode* resultNode;

    resultNode = findNodeInTree(rootNode, checkFunction, idToCheck);
    if (resultNode != nullptr)
        return resultNode;

    for (auto unparentedNode : unparentedNodes)
    {
        resultNode = findNodeInTree(unparentedNode, checkFunction, idToCheck);
        if (resultNode != nullptr)
            return resultNode;
    }

    return nullptr;
}

BTEditorNode* BehaviorTreeEditor::findNodeInTree(
    BTEditorNode* rootNode, const std::function<bool(BTEditorNode*, int)>& checkFunction, int idToCheck)
{
    std::queue<BTEditorNode*> searchQueue;
    searchQueue.push(rootNode);

    while (!searchQueue.empty())
    {
        BTEditorNode* nodeToCheck = searchQueue.front();
        searchQueue.pop();

        if (checkFunction(nodeToCheck, idToCheck))
            return nodeToCheck;

        for (auto childNodeLink : nodeToCheck->GetChildrenLinks())
        {
            searchQueue.push(childNodeLink.second);
        }
    }

    return nullptr;
}

Json BehaviorTreeEditor::toJson()
{
    Json json = Serializable::toJson();

    json["lastId"] = lastId;

    json["rootNode"] = rootNode->toJson();

    Json jsonNodeArray = Json::array();
    for (auto node : unparentedNodes)
    {
        jsonNodeArray.push_back(node->toJson());
    }
    json["unparentedNodes"] = jsonNodeArray;

    return json;
}

void BehaviorTreeEditor::fromJson(Json json)
{
    initVariable(json, "lastId", &lastId);

    BTEditorNode* node = getNodeFromJson(json["rootNode"]);
    rootNode = dynamic_cast<BTEditorNodeRoot*>(node);

    for (Json unparentedNodeJson : json["unparentedNodes"])
    {
        node = getNodeFromJson(unparentedNodeJson);
        if (node != nullptr)
            unparentedNodes.push_back(node);
    }
}

BTEditorNode* BehaviorTreeEditor::getNodeFromJson(Json json)
{
    std::string stringType;
    initVariable(json, "type", &stringType);
    BTNodeType type = MapUtils::TryGetByValue<BTNodeType, std::string>(
        MAP_NODE_TYPE_TO_STRING, stringType, BTNodeType::UNKNOWN);

    BTEditorNode* node = BTEditorNodeFactory::Create(type);
    if (node == nullptr)
        ErrorLogger::Log(Error,
            "BTEditorNode can't be created: " + stringType + "/n" + json.dump());

    return node;
}
