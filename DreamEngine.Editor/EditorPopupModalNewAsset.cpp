#include "EditorPopupModalNewAsset.h"
#include "AssetInfoFactory.h"

#include "imgui.h"

std::string EditorPopupModalNewAsset::GetAssetName()
{
    return assetNamePublic;
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
}

void EditorPopupModalNewAsset::onDrawPopup()
{
    static int currentType = 0;
    const char* firstLabel = tempStrMass[currentType].c_str();
    selectedAssetType = AssetInfoFactory::GetAssetTypeByString(tempStrMass[0]);
    
    if (ImGui::BeginCombo("Asset Type", firstLabel))
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

    static char assetName[128] = "";
    ImGui::InputText("Asset Name", assetName, IM_ARRAYSIZE(assetName));
    assetNamePublic = assetName;
}

bool EditorPopupModalNewAsset::onFinish()
{
    if (!result) return true;

    if (assetNamePublic.empty())
        return false;
    else
        return true;
}
