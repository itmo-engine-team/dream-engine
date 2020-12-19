#include "EditorPopupModalRenameFolder.h"

#include "imgui.h"

EditorPopupModalRenameFolder::EditorPopupModalRenameFolder(FolderNode* parentFolderNode, std::string oldName)
    : EditorPopupModalFolderBase("Rename Folder", parentFolderNode)
{
    oldFolderName = oldName;
}

std::string EditorPopupModalRenameFolder::GetNewFolderName()
{
    return newFolderName;
}

void EditorPopupModalRenameFolder::onDrawPopup()
{
    ImGui::Text("Current name: ");
    ImGui::SameLine();
    ImGui::Text(oldFolderName.c_str());

    static char folderName[128] = "";
    ImGui::InputText("New folder name", folderName, IM_ARRAYSIZE(folderName));
    newFolderName = folderName;
}

bool EditorPopupModalRenameFolder::onFinish()
{
    if (!result) return true;

    if (newFolderName.empty())
        return false;
    else
        return true;
}
