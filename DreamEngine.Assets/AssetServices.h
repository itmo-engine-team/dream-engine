#pragma once

#include "nlohmann/json.hpp"
#include <fstream>
#include <filesystem>

#include "AssetTree.h"



using json = nlohmann::json;

namespace AssetServices
{
    const std::string ASSET_FILE_EXTENSION = ".asset";

    json CreateAssetFile(AssetNode* node);
    void RemoveAssetFile(AssetNode* node);

    AssetTree* FindAssetTree(std::string rootNodeName);

    std::string CreateFolder(FolderNode* folderNode);
    void CheckFolderExist(std::filesystem::path fileRelativePath);
    FolderModificationResult RemoveFolder(FolderNode* folderNode, bool isRecursive);

    std::string CreateFolderPath(FolderNode* folderNode);
    std::string CreateAssetPath(AssetNode* assetNode);

    FolderModificationResult MoveFolder(FolderNode* folderNode, FolderNode* newParent);
    AssetModificationResult MoveAsset(AssetNode* assetNode, FolderNode* newParent);

    AssetTree* CreateDebugAssetTree();
}
