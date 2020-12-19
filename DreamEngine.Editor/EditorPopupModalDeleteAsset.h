#pragma once

#include "EditorPopupModal.h"

class AssetNode;

class EditorPopupModalDeleteAsset : public EditorPopupModal
{

public:

    EditorPopupModalDeleteAsset(AssetNode* currentAsset);

protected:

    void onDrawPopup() override;

};

