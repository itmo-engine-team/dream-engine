#pragma once

#include "nlohmann/json.hpp"
#include <fstream>
#include <filesystem>

using json = nlohmann::json;

namespace AssetServices
{
    json CreateAsset(std::string fileRelativePath);

    std::vector<json> FindAssets();

    void CheckAndCreateFolder(std::filesystem::path fileRelativePath);
}
