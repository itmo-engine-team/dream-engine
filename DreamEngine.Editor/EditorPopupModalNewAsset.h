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
    int currentType = 0;

    std::string assetName;
    std::string* tempStrMass;
    std::string label;

    AssetType selectedAssetType;

    void onDrawPopup() override;
    bool onFinish() override;

};

