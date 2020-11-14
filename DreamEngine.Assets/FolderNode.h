#pragma once

#include <string>
#include <vector>

#include "AssetServices.h"
#include "AssetNode.h"

class AssetNode;

class FolderNode
{

public:

    std::string GetName();
    FolderNode* GetParent();
    std::vector<FolderNode*> GetChildFolderList();
    std::vector<AssetNode*> GetChildAssetList();

protected:

    friend class AssetTree;

    FolderNode(std::string nodeName, FolderNode* parentNode);
    
    void setNodeName(std::string nodeName);
    void setParentNode(FolderNode* parentNode);

    void addChildFolderNode(FolderNode* childNode);
    void addChildFolderNodes(std::vector<FolderNode*> childNodes);
    void addChildAssetNode(AssetNode* childNode);
    void addChildAssetNodes(std::vector<AssetNode*> childNodes);

    void removeChildFolderNode(FolderNode* childNode);
    void removeChildAssetNode(AssetNode* childNode);

private:

    std::string name;
    FolderNode* parent;

    std::vector<FolderNode*> childFolderList;
    std::vector<AssetNode*> childAssetList;

};
