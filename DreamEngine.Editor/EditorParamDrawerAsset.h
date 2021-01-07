#pragma once

#include "EditorParamDrawer.h"
#include "ParamAsset.h"
#include "EditorPopupModalAssetChooser.h"

class EditorParamDrawerAsset : public EditorParamDrawer<ParamAsset>
{

public:

    EditorParamDrawerAsset(const std::string& name, BaseParam* baseParam);
    bool Draw() override;

private:

    EditorPopupModalAssetChooser* assetChooser;

};

