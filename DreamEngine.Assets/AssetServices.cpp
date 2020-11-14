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
    ClearAssetTree();

    std::string directory_name = "Content";
    std::string extension = ".asset";

    AssetTree* assetTree = &AssetTree::GetInstance();
    std::vector<FolderNode*> queueFolders;
    queueFolders.push_back(assetTree->GetRootNode());

    // Exception for directories not found
    try 
    {
        while(queueFolders.size() > 0)
        {
            FolderNode* currentFolderNode = queueFolders.at(0);

            std::filesystem::directory_iterator endIntr;
            for(std::filesystem::directory_iterator itr(directory_name); itr != endIntr; ++itr)
            {
                if(is_directory(itr->status()))
                {
                    FolderNode* childFolderNode = assetTree->CreateFolderNode(itr->path().filename().string(), currentFolderNode);
                    assetTree->AddFolderNode(childFolderNode, currentFolderNode);
                    queueFolders.push_back(childFolderNode);
                }
                else
                {
                    if (itr->path().extension() != extension) return;

                    AssetNode* childAssetNode = assetTree->CreateAssetNode(itr->path().filename().string(), currentFolderNode);
                    assetTree->AddAssetNode(childAssetNode, currentFolderNode);
                }
            }
        }
    }
    catch (std::exception& e)
    {
        std::cout << "Error: " << e.what() << '\n';
    }

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

void AssetServices::ClearAssetTree()
{
    AssetTree* assetTree = &AssetTree::GetInstance();
    assetTree->RemoveFolderNode(assetTree->GetRootNode(), true);
}

void CheckAndCreateFolder(std::filesystem::path fileRelativePath)
{
    if (!exists(fileRelativePath.parent_path()))
        create_directories(fileRelativePath.parent_path());
}

