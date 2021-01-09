#pragma once
#include "EditorWindow.h"
#include <BTEditorNode.h>
#include <BTNodeLogicType.h>

#include "imnodes.h"

class BTAssetInfo;

class EditorWindowBehaviorTreeViewport : public EditorWindow
{

public:

    EditorWindowBehaviorTreeViewport(Editor* editor, BTAssetInfo* assetInfo);
    ~EditorWindowBehaviorTreeViewport();

    void Init() override;
    void Update() override;
    void Render() override;

private:

    BTAssetInfo* assetInfo;
    BehaviorTreeEditor* BTEditor;
    BTEditorNode* currentNode;

    imnodes::EditorContext* context;

    std::string nodeName;
    std::string selectableName;

    int sizeStr;
    std::string* tempStrMass;
    std::string selectableLogicName;
    int currentType;
    BTNodeLogicType logicType;

    void setNodesPosition();
    void setNodePosition(BTEditorNode* root);
    void renderBTNodeEditor();
    void renderBTNodeInspector(BTEditorNode* node);
    void drawAddButtons(); 
    
    void drawNode(BTEditorNode* node, int nodeNumber);
    void drawNodes();
    int drawNodeTree(BTEditorNode* root, int nodeNumber = 0);
    void drawLink(BTEditorNode* root);
    void drawLinks();

    void saveBTAsset();
};

