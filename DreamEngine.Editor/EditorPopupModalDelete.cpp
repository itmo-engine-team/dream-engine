#include "EditorPopupModalDelete.h"

#include "imgui.h"

EditorPopupModalDelete::EditorPopupModalDelete(std::string name, bool isFolder)
    : EditorPopupModal(name)
{
    checkIsFolder = isFolder;
}

bool EditorPopupModalDelete::GetIsRecursive()
{
    return isRecursive;
}

void EditorPopupModalDelete::onDrawPopup()
{
    ImGui::Text("This operation cannot be undone!");
    if (checkIsFolder)
        ImGui::Checkbox("Delete folder with all files", &isRecursive);
}