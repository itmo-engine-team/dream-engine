#pragma once

#include "nlohmann/json.hpp"
#include <fstream>
#include <filesystem>

#include "AssetTree.h"

using json = nlohmann::json;

namespace AssetServices
{

    json CreateAsset(AssetNode* node);
    void RemoveAsset(AssetNode* node);

    AssetTree* FindAssetTree();

    void CheckAndCreateFolder(std::filesystem::path fileRelativePath);
    void RemoveFolder(FolderNode* folderNode, bool isRecursive);

    std::string CreateFolderPath(FolderNode* folderNode);
    std::string CreateAssetPath(AssetNode* assetNode);

}
