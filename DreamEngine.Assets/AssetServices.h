#pragma once

#include "nlohmann/json.hpp"
#include <fstream>
#include <filesystem>

#include "AssetNode.h"

using json = nlohmann::json;

namespace AssetServices
{

    json CreateAsset(AssetNode* node);
    void RemoveAsset(AssetNode* node);

    std::vector<json> FindAssets();

    void CheckAndCreateFolder(std::filesystem::path fileRelativePath);
    void RemoveFolder(FolderNode* folderNode, bool isRecursive);

    std::string CreateFolderPath(FolderNode* folderNode);

}
