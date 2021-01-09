#pragma once
#include "EditorWindow.h"
#include <BTEditorNode.h>

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

    void setNodesPosition();
    void setNodePosition(BTEditorNode* root);
    void renderBTNodeEditor();
    void renderBTNodeInspector(BTEditorNode* node);
    void drawAddButtons(); 
    
    void drawNode(BTEditorNode* node);
    void drawNodes();
    void drawNodeTree(BTEditorNode* root);
    void drawLink(BTEditorNode* root);
    void drawLinks();

    void saveBTAsset();
};

