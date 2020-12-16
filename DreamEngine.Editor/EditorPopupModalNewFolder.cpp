#include "EditorPopupModalNewFolder.h"

#include "imgui.h"

EditorPopupModalNewFolder::EditorPopupModalNewFolder(std::string name)
    : EditorPopupModal(name)
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
    if (folderNamePublic.empty())
        return false;
    else
        return true;
}
