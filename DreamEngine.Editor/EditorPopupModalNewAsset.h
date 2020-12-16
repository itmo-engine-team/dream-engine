#pragma once

#include "EditorPopupModalFolderBase.h"

#include <string>
#include "AssetInfoFactory.h"

class FolderNode;

class EditorPopupModalNewAsset : public EditorPopupModalFolderBase
{
public:

    EditorPopupModalNewAsset(FolderNode* parentFolderNode);

    std::string GetAssetName();

    // TODO move to protected
    AssetType selectedAssetType;

protected:

    int sizeStr;

    std::string assetNamePublic;
    std::string* tempStrMass;

    

    void onDrawPopup() override;
    bool onFinish() override;

};

