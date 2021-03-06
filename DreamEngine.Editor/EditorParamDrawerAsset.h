#pragma once

#include "EditorParamDrawer.h"
#include "ParamAsset.h"
#include "EditorPopupModalAssetChooser.h"

class EditorParamDrawerAsset : public EditorParamDrawer<ParamAsset>
{

public:

    EditorParamDrawerAsset(Editor* editor, int index, const std::string& name, BaseParam* baseParam);
    bool Draw() override;

private:

    Editor* editor;
    EditorPopupModalAssetChooser* assetChooser;
    AssetInfo* chosenAssetInfo;
    std::string inputFieldLabel;
};

