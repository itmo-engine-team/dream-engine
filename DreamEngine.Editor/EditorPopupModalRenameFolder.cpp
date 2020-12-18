#include "EditorPopupModalRenameFolder.h"

#include "imgui.h"

EditorPopupModalRenameFolder::EditorPopupModalRenameFolder(FolderNode* parentFolderNode)
    : EditorPopupModalFolderBase("Rename Folder", parentFolderNode)
{

}

std::string EditorPopupModalRenameFolder::GetNewFolderName()
{
    return newFolderName;
}

void EditorPopupModalRenameFolder::onDrawPopup()
{
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
