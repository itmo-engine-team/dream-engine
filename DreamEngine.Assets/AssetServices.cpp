#include "AssetServices.h"

#include <iomanip>
#include <iostream>

json AssetServices::CreateAsset(std::string fileRelativePath)
{
    json j;
    std::filesystem::path pathVar(fileRelativePath);

    CheckAndCreateFolder(pathVar);

    j["Object name"] = pathVar.stem().string();
    
    std::ofstream file(pathVar);
    file << std::setw(4) << j << std::endl;

    return j;
}

std::vector<json> AssetServices::FindAssets()
{
    std::vector<json> foundAssets;
    std::string directory_name = "Content";
    std::string extension = ".asset";

    // Exception for directories not found
    try 
    {
        // For all files in folders
        for (auto& p : std::filesystem::recursive_directory_iterator(directory_name)) 
        {
            if (p.path().extension() != extension)
                continue;

            std::ifstream file(p.path());
            json j;
            file >> j;

            foundAssets.push_back(j);
        }
    }
    catch (std::exception& e)
    {
        std::cout << "Error: " << e.what() << '\n';
    }

    return foundAssets;
}

void CheckAndCreateFolder(std::filesystem::path fileRelativePath)
{
    if (!exists(fileRelativePath.parent_path()))
        create_directories(fileRelativePath.parent_path());
}

