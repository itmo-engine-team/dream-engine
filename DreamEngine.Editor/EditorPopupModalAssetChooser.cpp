#include "EditorPopupModalAssetChooser.h"
#include "AssetInfoFactory.h"

#include "imgui.h"

EditorPopupModalAssetChooser::EditorPopupModalAssetChooser(Editor* editor, AssetType assetType)
    : EditorPopupModal("Asset Chooser"), assetType(assetType)
{
    assetManager = editor->GetContext()->GetAssetManager();
    assetMap = assetManager->GetAssetMapByType(assetType);

    assetIcon = editor->GetIconByAssetType(assetType);
}

AssetInfo* EditorPopupModalAssetChooser::GetChosenAsset() const
{
    return currentAsset;
}

AssetInfo* EditorPopupModalAssetChooser::getAssetInfoByName(std::string assetName)
{
    int i = 0;

    for (auto iterator = assetMap.begin(); iterator != assetMap.end(); ++iterator, i++)
    {
        if (iterator->second->GetName() == assetName)
        {
            return iterator->second;
        }
    }
}

void EditorPopupModalAssetChooser::onDrawPopup()
{
    static ImGuiTextFilter filter;
    filter.Draw();
    ImGui::Separator();

    int size = assetMap.size();
    int i = 0;
    filteringMass = new std::string[size];

    for (auto iterator = assetMap.begin(); iterator != assetMap.end(); ++iterator, i++)
    {
        filteringMass[i] = iterator->second->GetName();
    }

    for (i = 0; i < size; i++)
    {
        if (filter.PassFilter(filteringMass[i].c_str()))
        {
            const auto assetToDraw = getAssetInfoByName(filteringMass[i]);

            ImVec2 buttonSize(40, 40);
            ImGuiStyle& style = ImGui::GetStyle();
            float windowVisible = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

            ImGui::PushID(i);
            ImGui::BeginGroup();

            bool assetSelected = currentAsset == assetToDraw;
            if (assetSelected)
            {
                ImGui::PushStyleColor(ImGuiCol_Button, { 0.3, 0, 0.8, 1 });
            }

            if (ImGui::ImageButton(assetIcon->GetShaderResourceView(), buttonSize))
            {
                currentAsset = assetToDraw;
            }

            if (assetSelected)
            {
                ImGui::PopStyleColor();
            }

            ImGui::Text(assetToDraw->GetName().c_str());
            ImGui::EndGroup();

            float lastButton = ImGui::GetItemRectMax().x;
            float nextButton = lastButton + style.ItemSpacing.x + buttonSize.x; // Expected position if next button was on same line
            if (i + 1 < size && nextButton < windowVisible)
                ImGui::SameLine();
            ImGui::PopID();
        }
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
