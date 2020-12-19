#pragma once

#include "EditorPopupModal.h"

class AssetNode;

class EditorPopupModalDuplicateAsset : public EditorPopupModal
{

public:

    EditorPopupModalDuplicateAsset(AssetNode* assetNode);
    std::string GetNewAssetName();

protected:

    std::string newAssetName;

    void onDrawPopup() override;
    bool onFinish() override;

};

