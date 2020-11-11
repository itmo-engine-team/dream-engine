#pragma once

#include "nlohmann/json.hpp"
#include <fstream>
#include <filesystem>

#include "AssetNode.h"

using json = nlohmann::json;

namespace AssetServices
{
    json CreateAsset(AssetNode* node);

    std::vector<json> FindAssets();

    void CheckAndCreateFolder(std::filesystem::path fileRelativePath);

    std::string CreatePath(FolderNode* fNode, std::string pastPath);
}
