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
        std::string error = std::string("Remove asset error. Extension: ") + e.what();
        ErrorLogger::Log(Warning, error);
    }
}

AssetTree* AssetServices::FindAssetTree()
{
    std::string directory_name = "Content";
    std::string extension = ".asset";

    AssetTree* assetTree = &AssetTree::GetInstance();
    assetTree->ClearAssetTree();

    std::vector<FolderNode*> foldersQueue;
    foldersQueue.push_back(assetTree->GetRootNode());

    // Exception for directories not found
   
    while(foldersQueue.size() > 0)
    {
        FolderNode* currentFolderNode = foldersQueue.at(0);

        std::filesystem::directory_iterator endIntr;
        for(std::filesystem::directory_iterator itr(directory_name); itr != endIntr; ++itr)
        {
            if(is_directory(itr->status()))
            {
                FolderNode* childFolderNode = assetTree->CreateFolderNode(itr->path().filename().string(), currentFolderNode);
                foldersQueue.push_back(childFolderNode);
            }
            else
            {
                if (itr->path().extension() != extension) continue;

                assetTree->CreateAssetNode(itr->path().filename().string(), currentFolderNode); 
            }
        }
    }
    return assetTree;
}

void AssetServices::RemoveFolder(FolderNode* folderNode, bool isRecursive)
{
    std::filesystem::path pathVar(CreateFolderPath(folderNode));

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
    path = assetNode->GetName() + ".asset";

    FolderNode* currentNode = assetNode->GetParent();
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

