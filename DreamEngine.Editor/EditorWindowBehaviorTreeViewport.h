#pragma once
#include "EditorWindow.h"
#include <BTEditorNode.h>

class BTAssetInfo;

class EditorWindowBehaviorTreeViewport : public EditorWindow
{

public:

    EditorWindowBehaviorTreeViewport(Editor* editor, BTAssetInfo* assetInfo);

    void Init() override;
    void Update() override;
    void Render() override;

private:

    int idNode = 0;
    BTAssetInfo* assetInfo;
    BehaviorTreeEditor* BTEditor;

    void renderBTNodeEditor();
    void renderBTNodeInspector();
    void drawAddButtons();
    
    void drawNode(BTEditorNode* node);
    void drawNodes();
    void drawNodeTree(BTEditorNode* root);
    void drawLink(BTEditorNode* root);
    void drawLinks();
    void saveBTAsset();
};

