#pragma once

#include "EditorPopupModal.h"
#include "AssetInfoFactory.h"
#include <string>

class EditorPopupModalNewAsset : public EditorPopupModal
{
public:

    std::string GetAssetName();
    
    AssetType selectedAssetType;

    EditorPopupModalNewAsset(std::string name);

protected:

    int sizeStr;

    std::string assetNamePublic;
    std::string* tempStrMass;

    void onDrawPopup() override;
    bool onFinish() override;

};

