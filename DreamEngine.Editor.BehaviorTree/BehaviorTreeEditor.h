#pragma once

#include "Serializable.h"
#include "BTEditorNodeRoot.h"

class BTAssetInfo;

class BehaviorTreeEditor : Serializable
{

public:

    BehaviorTreeEditor();

    BTEditorNode* CreateNode(BTNodeType type, ImVec2 position = ImVec2(0, 0));
    void CreateLink(int parentAttributeId, int childAttributeId);

    BTEditorNode* GetRootNode() const;
    const std::vector<BTEditorNode*>& GetUnparentedNodes() const;

    // TODO: Methods to remove nodes and links

protected:

    friend BTAssetInfo;
    Json toJson() override;
    void fromJson(Json json) override;
    BTEditorNode* getNodeFromJson(Json json);

private:

    int lastId;

    BTEditorNodeRoot* rootNode;
    std::vector<BTEditorNode*> unparentedNodes;

    int generateNewId();
    void fillNodeIds(BTEditorNode* node);

    BTEditorNode* findNodeByParentAttributeId(int parentAttributeId);
    BTEditorNode* findNodeByChildrenAttributeId(int childrenAttributeId);
    BTEditorNode* findNode(const std::function<bool(BTEditorNode*, int)>& checkFunction, int idToCheck);
    BTEditorNode* findNodeInTree(BTEditorNode* rootNode,
        const std::function<bool(BTEditorNode*, int)>& checkFunction, int idToCheck);

};
