#include "EditorPopupModalRenameAsset.h"

#include "imgui.h"

EditorPopupModalRenameAsset::EditorPopupModalRenameAsset(AssetNode* currentAsset, std::string oldName)
    : EditorPopupModal("Rename Asset")
{
    oldAssetName = oldName;
}

std::string EditorPopupModalRenameAsset::GetNewAssetName()
{
    return newAssetName;
}

void EditorPopupModalRenameAsset::onDrawPopup()
{
    ImGui::Text("Current name: ");
    ImGui::SameLine();
    ImGui::Text(oldAssetName.c_str());

    static char assetName[128] = "";
    ImGui::InputText("New folder name", assetName, IM_ARRAYSIZE(assetName));
    newAssetName = assetName;
}

bool EditorPopupModalRenameAsset::onFinish()
{
    if (!result) return true;

    if (newAssetName.empty())
        return false;
    else
        return true;
}
