#include "EditorWindowBehaviorTreeViewport.h"

#include <queue>

#include "imgui.h"
#include "imnodes.h"
#include "Editor.h"
#include "AssetManager.h"
#include "BTAssetInfo.h"
#include "MapUtils.h"


EditorWindowBehaviorTreeViewport::EditorWindowBehaviorTreeViewport(Editor* editor, BTAssetInfo* assetInfo)
    : EditorWindow("Behavior Tree", editor), assetInfo(assetInfo)
{
    BTEditor = assetInfo->GetBTEditor();
}

void EditorWindowBehaviorTreeViewport::Init()
{

}

void EditorWindowBehaviorTreeViewport::Update()
{

}

void EditorWindowBehaviorTreeViewport::Render()
{
    renderBTNodeEditor();
    renderBTNodeInspector();
}

void EditorWindowBehaviorTreeViewport::renderBTNodeEditor()
{
    ImGui::Begin(GetName().data());

    if (ImGui::Button("Close"))
    {
        SetOpened(false);
    }
    ImGui::SameLine();
    if (ImGui::Button("Save"))
    {
        saveBTAsset();
    }

    drawAddButtons();
    ImGui::Separator();

    imnodes::BeginNodeEditor();

    drawNodes();
    drawLinks();

    imnodes::EndNodeEditor();
    
    int startId;
    int endId;
    bool result = imnodes::IsLinkCreated(&startId, &endId);
    if (result)
    {
        BTEditor->CreateLink(startId, endId);
    }

    ImGui::End();
}

void EditorWindowBehaviorTreeViewport::renderBTNodeInspector()
{
    ImGui::Begin("BT Node Inspector");

    ImGui::End();
}

void EditorWindowBehaviorTreeViewport::drawAddButtons()
{
    if (ImGui::Button("Add Composite"))
    {
        BTEditor->CreateNode(BTNodeType::Composite);
    }
    ImGui::SameLine();
    if (ImGui::Button("Add Logic"))
    {
        BTEditor->CreateNode(BTNodeType::Logic);
    }
}

void EditorWindowBehaviorTreeViewport::drawNode(BTEditorNode* node)
{
    imnodes::BeginNode(node->GetId());
    imnodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(node->GetName().c_str());
    imnodes::EndNodeTitleBar();

    if (node->CanHaveParent())
    {
        imnodes::BeginInputAttribute(node->GetParentAttributeId());
        imnodes::EndInputAttribute();
    }

    if (node->CanHaveChild())
    {
        imnodes::BeginOutputAttribute(node->GetChildrenAttributeId());
        imnodes::EndOutputAttribute();
    }

    ImGui::Indent(20);
    ImGui::TextUnformatted(node->GetTypeName().c_str());
    imnodes::EndNode();
}

void EditorWindowBehaviorTreeViewport::drawNodes()
{
    drawNodeTree(BTEditor->GetRootNode());
    for (auto currentNode : BTEditor->GetUnparentedNodes())
    {
        drawNodeTree(currentNode);
    }
}

void EditorWindowBehaviorTreeViewport::drawNodeTree(BTEditorNode* root)
{
    std::queue<BTEditorNode*> nodeQueue;
    nodeQueue.push(root);

    while (!nodeQueue.empty())
    {
        BTEditorNode* nodeToDraw = nodeQueue.front();
        nodeQueue.pop();

        drawNode(nodeToDraw);

        for (auto childNodeLink : nodeToDraw->GetChildrenLinks())
        {
            nodeQueue.push(childNodeLink.second);
        }
    }
}

void EditorWindowBehaviorTreeViewport::drawLinks()
{
    drawLink(BTEditor->GetRootNode());
    for (auto currentNode : BTEditor->GetUnparentedNodes())
    {
        drawLink(currentNode);
    }
}

void EditorWindowBehaviorTreeViewport::drawLink(BTEditorNode* root)
{
    std::queue<BTEditorNode*> nodeQueue;
    nodeQueue.push(root);

    while (!nodeQueue.empty())
    {
        BTEditorNode* nodeToDraw = nodeQueue.front();
        nodeQueue.pop();

        for (auto childNodeLink : nodeToDraw->GetChildrenLinks())
        {
            imnodes::Link(childNodeLink.first, nodeToDraw->GetChildrenAttributeId(), childNodeLink.second->GetChildrenAttributeId());
            nodeQueue.push(childNodeLink.second);
        }
    }
}

void EditorWindowBehaviorTreeViewport::saveBTAsset()
{
   editor->GetContext()->GetAssetManager()->SaveAsset(assetInfo->GetAssetNode());
}

