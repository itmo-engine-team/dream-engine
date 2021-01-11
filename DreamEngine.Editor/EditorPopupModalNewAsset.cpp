#include "EditorPopupModalNewAsset.h"
#include "AssetInfoFactory.h"

#include "imgui.h"

std::string EditorPopupModalNewAsset::GetAssetName()
{
    return assetName.c_str();
}

AssetType EditorPopupModalNewAsset::GetAssetType()
{
    return selectedAssetType;
}

EditorPopupModalNewAsset::EditorPopupModalNewAsset(FolderNode* parentFolderNode)
    : EditorPopupModalFolderBase("New Asset", parentFolderNode)
{
    sizeStr = MAP_ASSET_TYPE_TO_STRING.size();
    tempStrMass = new std::string[sizeStr];
    int i = 0;

    for (auto iterator = MAP_ASSET_TYPE_TO_STRING.begin();
        iterator != MAP_ASSET_TYPE_TO_STRING.end(); ++iterator, i++)
    {
        tempStrMass[i] = iterator->second;
    }

    selectedAssetType = AssetInfoFactory::GetAssetTypeByString(tempStrMass[0]);
    label = tempStrMass[0];

    assetName.resize(24);
}

void EditorPopupModalNewAsset::onDrawPopup()
{
    if (ImGui::BeginCombo("Asset Type", label.data()))
    {
        for (int n = 0; n < sizeStr; n++)
        {
            const bool isSelected = (currentType == n);

            if (ImGui::Selectable(tempStrMass[n].c_str(), isSelected))
            { 
                currentType = n;
                label = tempStrMass[currentType];
                selectedAssetType = AssetInfoFactory::GetAssetTypeByString(tempStrMass[n]);
            }
            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    ImGui::InputText("Asset Name", assetName.data(), 24);
}

bool EditorPopupModalNewAsset::onFinish()
{
    if (!result) return true;

    if (assetName.empty())
        return false;
    else
        return true;
}
