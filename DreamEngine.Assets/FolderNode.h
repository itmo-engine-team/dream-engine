#pragma once

#include <string>
#include <vector>

#include "AssetNode.h"

class AssetNode;

class FolderNode
{

public:

    std::string GetName();
    FolderNode* GetParent();
    std::vector<FolderNode*> GetChildFolderNode();
    std::vector<AssetNode*> GetChildAssetNode();

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
