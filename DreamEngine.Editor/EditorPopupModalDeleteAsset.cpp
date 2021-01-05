#include "EditorPopupModalDeleteAsset.h"

#include "imgui.h"

EditorPopupModalDeleteAsset::EditorPopupModalDeleteAsset(AssetNode* currentAsset)
    : EditorPopupModal("Delete Asset")
{
}

void EditorPopupModalDeleteAsset::onDrawPopup()
{
    ImGui::Text("This operation cannot be undone!");
}
