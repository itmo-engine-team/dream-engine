#pragma once

#include "EditorPopupModal.h"
#include "AssetInfoFactory.h"
#include <string>

class EditorPopupModalNewAsset : public EditorPopupModal
{
public:

    std::string assetNamePublic;
    AssetType selectedAssetType;

    EditorPopupModalNewAsset(std::string name);

protected:

    std::string text;
    AssetInfoFactory* assetFactory;

    void onDrawPopup() override;

};

