#include "AssetServices.h"

#include <iomanip>
#include <iostream>

json AssetServices::CreateAsset(AssetNode* node)
{
    json j;
    
    std::string pathVar(CreateAssetPath(node));

    CheckAndCreateFolder(pathVar);

    j["Object name"] = node->GetName();
    
    std::ofstream file(pathVar);
    file << std::setw(4) << j << std::endl;

    return j;
}

void AssetServices::RemoveAsset(AssetNode* node)
{
    std::filesystem::path pathVar(CreateAssetPath(node));
    try
    {
        remove(pathVar);
    }
    catch (std::exception& e)
    {
        std::cout << "Error: " << e.what() << '\n';
    }
}

AssetTree* AssetServices::FindAssetTree()
{
    AssetTree* assetTree;
    std::string directory_name = "Content";
    std::string extension = ".asset";

    //// Exception for directories not found
    //try 
    //{
    //    // For all files in folders
    //    for (auto& p : std::filesystem::recursive_directory_iterator(directory_name)) 
    //    {
    //        if (p.path().extension() != extension)
    //            continue;

    //        std::ifstream file(p.path());
    //        json j;
    //        file >> j;

    //        foundAssets.push_back(j);
    //    }
    //}
    //catch (std::exception& e)
    //{
    //    std::cout << "Error: " << e.what() << '\n';
    //}

    return assetTree;
}

void AssetServices::RemoveFolder(FolderNode* folderNode, bool isRecursive)
{
    std::filesystem::path pathVar(CreateFolderPath(folderNode->GetParent()));

    if (isRecursive)
        remove_all(pathVar);
    else
        remove(pathVar);
}

std::string AssetServices::CreateFolderPath(FolderNode* folderNode)
{
   std::string path;
   FolderNode* currentNode = folderNode;

   while(currentNode != nullptr )
   {
       path = currentNode->GetName() + "/" + path;
       currentNode = currentNode->GetParent();
   }

    return path;
}

std::string AssetServices::CreateAssetPath(AssetNode* assetNode)
{
    std::string path;
    FolderNode* currentNode = assetNode->GetParent();

    path = assetNode->GetName() + ".asset";

    while (currentNode != nullptr)
    {
        path = currentNode->GetName() + "/" + path;
        currentNode = currentNode->GetParent();
    }

    return path;
}

void CheckAndCreateFolder(std::filesystem::path fileRelativePath)
{
    if (!exists(fileRelativePath.parent_path()))
        create_directories(fileRelativePath.parent_path());
}

