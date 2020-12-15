#include "EditorPopupModalNew.h"
#include "AssetInfoFactory.h"

#include "imgui.h"

EditorPopupModalNew::EditorPopupModalNew(std::string name)
    : EditorPopupModal(name)
{
    assetFactory = new AssetInfoFactory();
}

void EditorPopupModalNew::onDrawPopup()
{
    int sizeStr = assetFactory->MAP_ASSET_TYPE_TO_STRING.size();
    std::string* tempStrMass = new std::string[sizeStr];
    int i = 0;

    for (auto iterator = assetFactory->MAP_ASSET_TYPE_TO_STRING.begin(); iterator != assetFactory->MAP_ASSET_TYPE_TO_STRING.end(); ++iterator)
    {
        tempStrMass[i] = assetFactory->GetAssetTypeStringName(iterator->first);
        i++;
    }

    static int currentType = 0;
    const char* firstLabel = tempStrMass[currentType].c_str();
    selectedAssetType = assetFactory->GetAssetTypeByString(tempStrMass[0]);
    
    if (ImGui::BeginCombo("Asset Type", firstLabel))
    {
        for (int n = 0; n < sizeStr; n++)
        {
            const bool is_selected = (currentType == n);

            if (ImGui::Selectable(tempStrMass[n].c_str(), is_selected))
            {
                currentType = n;
                selectedAssetType = assetFactory->GetAssetTypeByString(tempStrMass[n]);
            }
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    static char assetName[128] = "";
    ImGui::InputText("Asset Name", assetName, IM_ARRAYSIZE(assetName));
    assetNamePublic = assetName;
}
