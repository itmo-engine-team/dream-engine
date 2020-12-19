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

    AssetType GetAssetType();
    

protected:

    int sizeStr;

    std::string assetNamePublic;
    std::string* tempStrMass;

    AssetType selectedAssetType;

    void onDrawPopup() override;
    bool onFinish() override;

};

