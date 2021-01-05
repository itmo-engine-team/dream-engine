#include "EditorPopupModalDeleteFolder.h"

#include "imgui.h"

EditorPopupModalDeleteFolder::EditorPopupModalDeleteFolder(FolderNode* parentFolderNode)
    : EditorPopupModalFolderBase("Delete", parentFolderNode)
{

}

bool EditorPopupModalDeleteFolder::GetIsRecursive()
{
    return isRecursive;
}

void EditorPopupModalDeleteFolder::onDrawPopup()
{
    ImGui::Text("This operation cannot be undone!");
    ImGui::Checkbox("Delete folder with all files", &isRecursive);
}
