#include "EditorParamDrawerAsset.h"

#include "imgui.h"

EditorParamDrawerAsset::EditorParamDrawerAsset(const std::string& name, BaseParam* baseParam)
    : EditorParamDrawer<ParamAsset>(name, baseParam)
{
    //assetChooser = new EditorPopupModalAssetChooser(param->GetAssetType());

}

bool EditorParamDrawerAsset::Draw()
{
    ImGui::Text(name.c_str());
    return false;
}
