#include "EditorPopupModalDuplicateAsset.h"

#include "imgui.h"

EditorPopupModalDuplicateAsset::EditorPopupModalDuplicateAsset(AssetNode* currentAsset)
    : EditorPopupModal("Duplicate Asset")
{

}

std::string EditorPopupModalDuplicateAsset::GetNewAssetName()
{
    return newAssetName;
}

void EditorPopupModalDuplicateAsset::onDrawPopup()
{
    static char assetName[128] = "";
    ImGui::InputText("New Asset Name", assetName, IM_ARRAYSIZE(assetName));
    newAssetName = assetName;
}

bool EditorPopupModalDuplicateAsset::onFinish()
{
    if (!result) return true;

    if (newAssetName.empty())
        return false;
    else
        return true;
}
