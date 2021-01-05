#include "EditorWindowBehaviorTreeViewport.h"

#include "imgui.h"
#include "imnodes.h"
#include "Editor.h"


EditorWindowBehaviorTreeViewport::EditorWindowBehaviorTreeViewport(Editor* editor)
    : EditorWindow("Behavior Tree", editor)
{

}

void EditorWindowBehaviorTreeViewport::Init()
{

}

void EditorWindowBehaviorTreeViewport::Update()
{
    
}

void EditorWindowBehaviorTreeViewport::Render()
{

    ImGui::Begin(GetName().data());

    imnodes::BeginNodeEditor();
    imnodes::BeginNode(1);

    imnodes::BeginNodeTitleBar();
    ImGui::TextUnformatted("simple node :)");
    imnodes::EndNodeTitleBar();

    imnodes::BeginInputAttribute(2);
    ImGui::Text("input");
    imnodes::EndInputAttribute();

    imnodes::BeginOutputAttribute(3);
    ImGui::Indent(40);
    ImGui::Text("output");
    imnodes::EndOutputAttribute();

    imnodes::EndNode();
    imnodes::EndNodeEditor();

    ImGui::End();

}
