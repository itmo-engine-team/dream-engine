#include "AssetServices.h"

#include <iomanip>
#include <iostream>


#include "ErrorLogger.h"

json AssetServices::CreateAssetFile(AssetNode* node)
{
    json j;

    const std::string pathVar(CreateAssetPath(node));

    CheckFolderExist(pathVar);

    j["Object name"] = node->GetName();

    std::ofstream file(pathVar);
    file << std::setw(4) << j << std::endl;

    return j;
}

void AssetServices::RemoveAssetFile(AssetNode* node)
{
    const std::filesystem::path pathVar(CreateAssetPath(node));
    
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

AssetTree* AssetServices::FindAssetTree(std::string rootNodeName)
{
    const std::string directoryName = rootNodeName;
    const std::string extension = ".asset";

    AssetTree* assetTree = new AssetTree(rootNodeName);
    CreateFolder(assetTree->GetRootNode());

    std::vector<FolderNode*> foldersQueue;
    foldersQueue.push_back(assetTree->GetRootNode());

    while (!foldersQueue.empty())
    {
        FolderNode* currentFolderNode = foldersQueue.at(0);
        foldersQueue.erase(foldersQueue.begin());

        const std::string pathVar = CreateFolderPath(currentFolderNode);

        std::filesystem::directory_iterator endItr;
        for (std::filesystem::directory_iterator itr(pathVar); itr != endItr; ++itr)
        {
            if (is_directory(itr->status()))
            {        
                FolderModificationResult childFolderStruct = assetTree->CreateFolderNode(
                    itr->path().filename().string(), currentFolderNode);
                if(childFolderStruct.resault)
                    foldersQueue.push_back(childFolderStruct.folderNode);
            }
            else
            {
                if (itr->path().extension() != extension) continue;

                // TODO implement converting json file to AssetInfo
                AssetInfo* assetInfo = nullptr;

                assetTree->CreateAssetNode(
                    assetInfo, itr->path().stem().string(), currentFolderNode);
            }
        }
    }
    return assetTree;
}

std::string AssetServices::CreateFolder(FolderNode* folderNode)
{
    const std::string pathVar(CreateFolderPath(folderNode));
    CheckFolderExist(pathVar);
    return pathVar;
}

void AssetServices::RemoveFolder(FolderNode* folderNode, const bool isRecursive)
{
    const std::filesystem::path oldPath(CreateFolderPath(folderNode));

    if (isRecursive)
    {
        remove_all(oldPath);
        return;
    }

    const std::string parentPath(CreateFolderPath(folderNode->GetParent()));

    std::filesystem::directory_iterator endItr;
    for (std::filesystem::directory_iterator itr(oldPath); itr != endItr; ++itr)
    {
        std::filesystem::path newPath = parentPath + itr->path().filename().string();

        if (!MoveFileEx(itr->path().c_str(), newPath.c_str(), MOVEFILE_WRITE_THROUGH))
        {
           std::string error = std::string("MoveFileEx failed with error %d\n", GetLastError());
           ErrorLogger::Log(Warning, error);
        }
            
    }
    remove(oldPath);
}

std::string AssetServices::CreateFolderPath(FolderNode* folderNode)
{
    std::string path;
    FolderNode* currentNode = folderNode;

    while (currentNode != nullptr)
    {
        path = currentNode->GetName() + "/" + path;
        currentNode = currentNode->GetParent();
    }
    return path;
}

std::string AssetServices::CreateAssetPath(AssetNode* assetNode)
{
    std::string path = CreateFolderPath(assetNode->GetParent()) +
        "/" + assetNode->GetName() + ".asset";

    return path;
}

void AssetServices::MoveFolder(FolderNode* folderNode, FolderNode* newParent)
{
    const std::filesystem::path oldPath = CreateFolderPath(folderNode);
    const std::string parentPath = CreateFolderPath(newParent);
    const std::filesystem::path newPath = parentPath + folderNode->GetName();
    
    if (!MoveFileEx(oldPath.c_str(), newPath.c_str(), MOVEFILE_WRITE_THROUGH))
    {
        std::string error = "MoveFileEx failed with error: " + GetLastError();
        ErrorLogger::Log(Warning, error);
    }
}

void AssetServices::MoveAsset(AssetNode* assetNode, FolderNode* newParent)
{
    const std::filesystem::path oldPath = CreateAssetPath(assetNode);
    const std::string parentPath = CreateFolderPath(newParent);
    const std::filesystem::path newPath = parentPath + assetNode->GetName();

    if (!MoveFileEx(oldPath.c_str(), newPath.c_str(), MOVEFILE_WRITE_THROUGH))
    {
        std::string error = std::string("MoveFileEx failed with error %d\n", GetLastError());
        ErrorLogger::Log(Warning, error);
    }
}

void AssetServices::CheckFolderExist(std::filesystem::path fileRelativePath)
{
    if (!exists(fileRelativePath.parent_path()))
        create_directories(fileRelativePath.parent_path());
}

