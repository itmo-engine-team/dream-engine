#include "AssetServices.h"

#include <iomanip>
#include <iostream>


json AssetServices::CreateAsset(AssetNode* node)
{
    json j;
    
    std::filesystem::path pathVar(CreatePath(node->GetParentNode(), node->GetNodeName()));

    CheckAndCreateFolder(pathVar);

    j["Object name"] = node->GetNodeName();
    
    std::ofstream file(pathVar);
    file << std::setw(4) << j << std::endl;

    return j;
}

void AssetServices::RemoveAsset(AssetNode* node)
{
    std::filesystem::path pathVar(CreatePath(node->GetParentNode(), node->GetNodeName()));
    try
    {
        remove(pathVar);
    }
    catch (std::exception& e)
    {
        std::cout << "Error: " << e.what() << '\n';
    }
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

std::string AssetServices::CreatePath(FolderNode* fNode, std::string pastPath)
{
    std::string path = pastPath;
    path = fNode->GetNodeName() + "/" + path;

    if (fNode->GetParentNode() != nullptr)
       path = CreatePath(fNode->GetParentNode(), path);

    return path;
}

void CheckAndCreateFolder(std::filesystem::path fileRelativePath)
{
    if (!exists(fileRelativePath.parent_path()))
        create_directories(fileRelativePath.parent_path());
}

