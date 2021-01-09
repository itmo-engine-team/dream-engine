#pragma once

#include "EditorPopupModal.h"
#include "AssetManager.h"
#include "Texture.h"
#include "Editor.h"

class EditorPopupModalAssetChooser : public EditorPopupModal
{
public:

    EditorPopupModalAssetChooser(Editor* editor, AssetType assetType);
    ~EditorPopupModalAssetChooser();

    AssetInfo* GetChosenAsset() const;

protected:

    AssetManager* assetManager;
    AssetType assetType;
    Texture* assetIcon;
    Texture* noneIcon;
    AssetInfo* currentAsset;
    std::map<unsigned int, AssetInfo*> assetMap;

    void onDrawPopup() override;
    bool onFinish() override;
};

