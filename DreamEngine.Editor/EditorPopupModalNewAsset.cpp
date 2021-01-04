#include "EditorPopupModalNewAsset.h"
#include "AssetInfoFactory.h"

#include "imgui.h"

std::string EditorPopupModalNewAsset::GetAssetName()
{
    return assetName;
}

AssetType EditorPopupModalNewAsset::GetAssetType()
{
    return selectedAssetType;
}

EditorPopupModalNewAsset::EditorPopupModalNewAsset(FolderNode* parentFolderNode)
    : EditorPopupModalFolderBase("New Asset", parentFolderNode)
{
    sizeStr = AssetInfoFactory::MAP_ASSET_TYPE_TO_STRING.size();
    tempStrMass = new std::string[sizeStr];
    int i = 0;

    for (auto iterator = AssetInfoFactory::MAP_ASSET_TYPE_TO_STRING.begin(); iterator != AssetInfoFactory::MAP_ASSET_TYPE_TO_STRING.end(); ++iterator, i++)
    {
        tempStrMass[i] = AssetInfoFactory::GetAssetTypeStringName(iterator->first);
    }

    selectedAssetType = AssetInfoFactory::GetAssetTypeByString(tempStrMass[0]);

    assetName.resize(24);
}

void EditorPopupModalNewAsset::onDrawPopup()
{
    label = tempStrMass[currentType];

    if (ImGui::BeginCombo("Asset Type", label.data()))
    {
        for (int n = 0; n < sizeStr; n++)
        {
            const bool isSelected = (currentType == n);

            if (ImGui::Selectable(tempStrMass[n].c_str(), isSelected))
            {
                currentType = n;
                selectedAssetType = AssetInfoFactory::GetAssetTypeByString(tempStrMass[n]);
            }
            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    ImGui::InputText("Asset Name", assetName.data(), 256);
}

bool EditorPopupModalNewAsset::onFinish()
{
    if (!result) return true;

    if (assetName.empty())
        return false;
    else
        return true;
}
