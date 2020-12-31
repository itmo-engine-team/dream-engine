#include "EditorPopupModalAssetChooser.h"
#include "AssetInfoFactory.h"

#include "imgui.h"

EditorPopupModalAssetChooser::EditorPopupModalAssetChooser(Editor* editor, AssetType currentAssetType, Texture* texture)
    : EditorPopupModal("Asset Chooser")
{
    assetManager = editor->GetContext()->GetAssetManager();
    assetType = currentAssetType;
    assetIcon = texture;

    assetMap = assetManager->GetAssetMapByType(assetType);
}

AssetInfo* EditorPopupModalAssetChooser::GetCurrentAsset()
{
    return currentAsset;
}

void EditorPopupModalAssetChooser::onDrawPopup()
{
    ImVec2 buttonSize(40, 40);
    ImGuiStyle& style = ImGui::GetStyle();
    float windowVisible = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

    int assetSize = assetMap.size();
    int i = 0;

    for (auto iterator = assetMap.begin(); iterator != assetMap.end(); ++iterator, i++)
    {

        ImGui::PushID(i);
        ImGui::BeginGroup();
        if (ImGui::ImageButton(assetIcon->GetShaderResourceView(), buttonSize))
        {
            currentAsset = iterator->second;
        }

        ImGui::Text(iterator->second->GetName().c_str());
        ImGui::EndGroup();

        float lastButton = ImGui::GetItemRectMax().x;
        float nextButton = lastButton + style.ItemSpacing.x + buttonSize.x; // Expected position if next button was on same line
        if (i + 1 < assetSize && nextButton < windowVisible)
            ImGui::SameLine();
        ImGui::PopID();
    }
}

bool EditorPopupModalAssetChooser::onFinish()
{
    if (!result) return true;

    if (!currentAsset)
        return false;
    else
        return true;
}
