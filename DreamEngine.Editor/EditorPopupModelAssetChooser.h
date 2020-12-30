#pragma once
#include "EditorPopupModal.h"
#include "AssetManager.h"
#include "Texture.h"
#include "Editor.h"

#include "imgui.h"

class EditorPopupModelAssetChooser : public EditorPopupModal
{
public:

    EditorPopupModelAssetChooser(Editor* editor, AssetType currentAssetType, Texture* texture);

    AssetInfo* GetCurrentAsset();

protected:

    AssetManager* assetManager;
    AssetType assetType;
    Texture* assetIcon;
    AssetInfo* currentAsset;

    void onDrawPopup() override;
    bool onFinish() override;
};

