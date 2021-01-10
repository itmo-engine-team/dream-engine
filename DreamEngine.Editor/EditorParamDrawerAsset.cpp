#include "EditorParamDrawerAsset.h"

#include "imgui.h"

EditorParamDrawerAsset::EditorParamDrawerAsset(Editor* editor,
    int index, const std::string& name, BaseParam* baseParam)
    : EditorParamDrawer<ParamAsset>(index, name, baseParam), editor(editor)
{
    assetChooser = nullptr;

    if (!param->IsDefault())
    {
        // Find asset if it was selected previously
        chosenAssetInfo = editor->GetContext()->GetAssetManager()->GetAssetByType(
            param->GetAssetType(), param->Get());
    }
}

bool EditorParamDrawerAsset::Draw()
{
    ImGui::Text(param->IsDefault() ? "None" : chosenAssetInfo->GetName().c_str());

    ImGui::SameLine();
    if (ImGui::Button(name.c_str()))
    {
        assetChooser = new EditorPopupModalAssetChooser(editor, param->GetAssetType());
    }

    if (assetChooser == nullptr)
        return false;

    if (!EditorPopupModal::DrawPipeline(assetChooser))
        return false;

    bool isChanged = assetChooser->GetResult();
    if (isChanged)
    {
        chosenAssetInfo = assetChooser->GetChosenAsset();
        if (chosenAssetInfo != nullptr)
            param->Set(chosenAssetInfo->GetId());
        else
            param->SetDef();
    }

    delete assetChooser;
    assetChooser = nullptr;

    return isChanged;
}
