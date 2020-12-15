#pragma once

#include "EditorPopupModal.h"
#include "AssetInfoFactory.h"
#include <string>

class EditorPopupModalNew : public EditorPopupModal
{
public:

    std::string assetNamePublic;
    AssetType selectedAssetType;

    EditorPopupModalNew(std::string name);

protected:

    std::string text;
    AssetInfoFactory* assetFactory;

    void onDrawPopup() override;

};

