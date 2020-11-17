#pragma once

#include <string>

#include "FolderNode.h"
#include "AssetInfo.h"

class FolderNode;

class AssetNode
{

public:

    AssetInfo* GetAssetInfo() const;

    std::string GetName() const;
    FolderNode* GetParent() const;

protected:

    friend class AssetTree;
    friend class FolderNode;

    AssetNode(AssetInfo* assetInfo, std::string nodeName, FolderNode* parentNode);

    void setNodeName(std::string nodeName);
    void setParentNode(FolderNode* parentNode);

private:

    AssetInfo* assetInfo;

    std::string name;
    FolderNode* parent;

};
