#pragma once
#include "EditorPopupModal.h"
#include "AssetManager.h"
#include "Texture.h"
#include "Editor.h"

class EditorPopupModalAssetChooser : public EditorPopupModal
{
public:

    EditorPopupModalAssetChooser(Editor* editor, AssetType currentAssetType, Texture* texture);

    AssetInfo* GetCurrentAsset();

protected:

    AssetManager* assetManager;
    AssetType assetType;
    Texture* assetIcon;
    AssetInfo* currentAsset;
    std::map<unsigned int, AssetInfo*> assetMap;

    void onDrawPopup() override;
    bool onFinish() override;
};

