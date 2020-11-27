#pragma once

#include "nlohmann/json.hpp"
#include <fstream>
#include <filesystem>

#include "AssetTree.h"

using json = nlohmann::json;

namespace AssetServices
{

    json CreateAssetFile(AssetNode* node);
    void RemoveAssetFile(AssetNode* node);

    AssetTree* FindAssetTree(std::string rootNodeName);

    void CheckAndCreateFolder(std::filesystem::path fileRelativePath);
    void RemoveFolder(FolderNode* folderNode, bool isRecursive);

    std::string CreateFolderPath(FolderNode* folderNode);
    std::string CreateAssetPath(AssetNode* assetNode);

}
