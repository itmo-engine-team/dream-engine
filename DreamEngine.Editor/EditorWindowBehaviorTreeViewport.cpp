#include "EditorWindowBehaviorTreeViewport.h"

#include "imgui.h"
#include "imnodes.h"
#include "Editor.h"

EditorWindowBehaviorTreeViewport::EditorWindowBehaviorTreeViewport(Editor* editor)
    : EditorWindow("Behavior Tree", editor)
{

}

void EditorWindowBehaviorTreeViewport::Update()
{
    
}

void EditorWindowBehaviorTreeViewport::Render()
{
    beginDrawEditor();
    drawSequence();
    endDrawEditor();
}

void EditorWindowBehaviorTreeViewport::beginDrawEditor()
{
    ImGui::Begin(GetName().data());

    imnodes::BeginNodeEditor();
}

void EditorWindowBehaviorTreeViewport::drawSequence()
{
    imnodes::BeginNode(1);

    imnodes::BeginNodeTitleBar();

    imnodes::BeginInputAttribute(2);
    ImGui::Text(" ");
    imnodes::EndInputAttribute(); 
    
    imnodes::EndNodeTreeTitleBar();

    imnodes::BeginOutputAttribute(3);
    ImGui::Indent(40);
    ImGui::Text("      ");
    imnodes::EndOutputAttribute();

    imnodes::EndCustomNode();
}

void EditorWindowBehaviorTreeViewport::endDrawEditor()
{
    imnodes::EndCustomNodeEditor();

    ImGui::End();
}
