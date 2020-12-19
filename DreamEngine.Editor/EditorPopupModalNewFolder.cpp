#include "EditorPopupModalNewFolder.h"

#include "imgui.h"

EditorPopupModalNewFolder::EditorPopupModalNewFolder(FolderNode* parentFolderNode)
    : EditorPopupModalFolderBase("New Folder", parentFolderNode)
{

}

std::string EditorPopupModalNewFolder::GetFolderName()
{
    return folderNamePublic;
}

void EditorPopupModalNewFolder::onDrawPopup()
{
    static char folderName[128] = "";
    ImGui::InputText("Asset Name", folderName, IM_ARRAYSIZE(folderName));
    folderNamePublic = folderName;
}

bool EditorPopupModalNewFolder::onFinish()
{
    if (!result) return true;

    if (folderNamePublic.empty())
        return false;
    else
        return true;
}
