#pragma once

#include "EditorPopupModal.h"
#include "AssetManager.h"
#include "Texture.h"
#include "Editor.h"

class EditorPopupModalAssetChooser : public EditorPopupModal
{
public:

    EditorPopupModalAssetChooser(Editor* editor, AssetType assetType);

    AssetInfo* GetChosenAsset() const;

protected:

    AssetManager* assetManager;
    AssetType assetType;
    Texture* assetIcon;
    AssetInfo* currentAsset;
    std::map<unsigned int, AssetInfo*> assetMap;

    std::string* filteringMass;

    AssetInfo* getAssetInfoByName(std::string assetName);

    void onDrawPopup() override;
    bool onFinish() override;
};

