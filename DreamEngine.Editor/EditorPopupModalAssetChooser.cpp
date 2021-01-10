#include "EditorPopupModalAssetChooser.h"
#include "AssetInfoFactory.h"

#include "imgui.h"

EditorPopupModalAssetChooser::EditorPopupModalAssetChooser(Editor* editor, AssetType assetType)
    : EditorPopupModal("Asset Chooser"), assetType(assetType)
{
    assetManager = editor->GetContext()->GetAssetManager();
    assetMap = assetManager->GetAssetMapByType(assetType);

    assetIcon = editor->GetIconByAssetType(assetType);
    noneIcon = new Texture(editor->GetContext()->GetGraphics(), editor->GetPathFromEditor(L"Icons/noneIcon.png").c_str());

    currentAsset = nullptr;
}

EditorPopupModalAssetChooser::~EditorPopupModalAssetChooser()
{
    delete noneIcon;
}

AssetInfo* EditorPopupModalAssetChooser::GetChosenAsset() const
{
    return currentAsset;
}

void EditorPopupModalAssetChooser::onDrawPopup()
{
    static ImGuiTextFilter filter;
    filter.Draw();
    ImGui::Separator();
    
    int i = 0;  
    drawElement(i, nullptr, "None");
    i++;

    for (auto iterator = assetMap.begin(); iterator != assetMap.end(); ++iterator, i++)
    {
        const auto assetToDraw = iterator->second;

        if (filter.PassFilter(assetToDraw->GetName().c_str()))
        { 
            drawElement(i, assetToDraw, assetToDraw->GetName().c_str());
        }
    }
}

bool EditorPopupModalAssetChooser::onFinish()
{
    if (!result) return true;
}

void EditorPopupModalAssetChooser::drawElement(int index, AssetInfo* assetToDraw, const std::string &assetName)
{
    ImVec2 buttonSize(40, 40);
    ImGuiStyle& style = ImGui::GetStyle();
    float windowVisible = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

    ImGui::PushID(index);
    ImGui::BeginGroup();

    bool assetSelected = currentAsset == assetToDraw;
    if (assetSelected)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, { 0.3, 0, 0.8, 1 });
    }

    if (ImGui::ImageButton(assetToDraw != nullptr ? assetIcon->GetShaderResourceView() : noneIcon->GetShaderResourceView(), buttonSize))
    {
        currentAsset = assetToDraw;
    }

    if (assetSelected)
    {
        ImGui::PopStyleColor();
    }

    ImGui::Text(assetName.c_str());
    ImGui::EndGroup();

    float lastButton = ImGui::GetItemRectMax().x;
    float nextButton = lastButton + style.ItemSpacing.x + buttonSize.x; // Expected position if next button was on same line
    if (index + 1 < assetMap.size() + 1 && nextButton < windowVisible)
        ImGui::SameLine();
    ImGui::PopID();
}
