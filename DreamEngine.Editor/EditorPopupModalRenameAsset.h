#pragma once

#include "EditorPopupModal.h"

class AssetNode;

class EditorPopupModalRenameAsset : public EditorPopupModal
{
public:

    EditorPopupModalRenameAsset(AssetNode* currentAsset, std::string oldName);
    std::string GetNewAssetName();

protected:

    std::string oldAssetName;
    std::string newAssetName;

    void onDrawPopup() override;
    bool onFinish() override;
};

