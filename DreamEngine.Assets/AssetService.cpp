#include "AssetService.h"

#include <iomanip>
#include <iostream>

#include "AssetInfoFactory.h"
#include "Serializable.h"
#include "ErrorLogger.h"

AssetModificationResult AssetService::CreateAssetFile(AssetNode* node)
{
    const std::string pathVar(CreateAssetPath(node));

    checkFolderExist(pathVar);

    if (!std::filesystem::exists(pathVar))
        return { false, node, "File already exist"};

    Json j = node->GetAssetInfo()->toJson();

    std::ofstream file(pathVar);
    file << std::setw(4) << j << std::endl;
    return  { true, node };
}

AssetModificationResult AssetService::RemoveAssetFile(AssetNode* node)
{
    const std::filesystem::path pathVar(CreateAssetPath(node));

    try
    {
        remove(pathVar);
        return { true, node };
    }
    catch (std::exception& e)
    {
        std::string error = std::string("Remove asset error. ") + e.what();
        ErrorLogger::Log(Warning, error);
        return { false, node, error };
    }
}

AssetTree* AssetService::FindAssetTree(std::string rootNodeName)
{
    const std::string directoryName = rootNodeName;

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
                FolderModificationResult childFolderResult = assetTree->CreateFolderNode(
                    itr->path().filename().string(), currentFolderNode);
                if (childFolderResult.isSuccess)
                    foldersQueue.push_back(childFolderResult.node);
            }
            else
            {
                if (itr->path().extension() != ASSET_FILE_EXTENSION) continue;

                std::ifstream file(itr->path().c_str());
                Json json;
                file >> json;


                std::string stringAssetType;
                if (!json.contains("type"))
                {
                    ErrorLogger::Log(Error, "Asset " + itr->path().string() + " has no type attribute");
                    continue;
                }

                stringAssetType = json["type"].get<std::string>();
                AssetType assetType = AssetInfoFactory::GetAssetTypeByString(stringAssetType);
                AssetInfo* assetInfo = AssetInfoFactory::Create(assetType);
                assetInfo->fromJson(json);

                assetTree->CreateAssetNode(
                    assetInfo, itr->path().stem().string(), currentFolderNode);
            }
        }
    }
    return assetTree;
}

AssetModificationResult AssetService::SaveAsset(AssetNode* assetNode)
{
    std::filesystem::path path = CreateAssetPath(assetNode);

    Json j = assetNode->GetAssetInfo()->toJson();
    std::ofstream file(path);
    file << std::setw(4) << j << std::endl;

    return { true };
}

FolderModificationResult AssetService::CreateFolder(FolderNode* folderNode)
{
    const std::string pathVar(CreateFolderPath(folderNode));
    bool result = checkFolderExist(pathVar);
    if (result)
        return { true, folderNode };

    return { false, folderNode, "Folder already exist" };
}

FolderModificationResult AssetService::RemoveFolder(FolderNode* folderNode, const bool isRecursive)
{
    const std::filesystem::path oldPath(CreateFolderPath(folderNode));

    if (isRecursive)
    {
        remove_all(oldPath);
        return { true };
    }

    const std::string parentPath(CreateFolderPath(folderNode->GetParent()));

    std::filesystem::directory_iterator endItr;
    for (std::filesystem::directory_iterator itr(oldPath); itr != endItr; ++itr)
    {
        std::filesystem::path newPath = parentPath + itr->path().filename().string();

        if (!MoveFileEx(itr->path().c_str(), newPath.c_str(), MOVEFILE_WRITE_THROUGH))
        {

            FolderModificationResult folderResult = { false, nullptr, std::string(
                "MoveFileEx failed with error %d\n", GetLastError())
            };
            folderResult.node = folderNode;

            ErrorLogger::Log(Warning, folderResult.error);
            return folderResult;
        }

    }
    remove(oldPath);

    return { true };
}

std::string AssetService::CreateFolderPath(FolderNode* folderNode)
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

std::string AssetService::CreateAssetPath(AssetNode* assetNode)
{
    std::string path = CreateFolderPath(assetNode->GetParent()) +
        "/" + assetNode->GetName() + ASSET_FILE_EXTENSION;

    return path;
}

FolderModificationResult AssetService::MoveFolder(FolderNode* folderNode, FolderNode* newParent)
{
    const std::filesystem::path oldPath = CreateFolderPath(folderNode);
    const std::string parentPath = CreateFolderPath(newParent);
    const std::filesystem::path newPath = parentPath + folderNode->GetName();

    if (!MoveFileEx(oldPath.c_str(), newPath.c_str(), MOVEFILE_WRITE_THROUGH))
    {
        FolderModificationResult folderResult = { false, nullptr, std::string(
            "MoveFileEx failed with error %d\n", GetLastError())
        };

        ErrorLogger::Log(Warning, folderResult.error);
        return folderResult;
    }

    return { true, folderNode };
}

AssetModificationResult AssetService::MoveAsset(AssetNode* assetNode, FolderNode* newParent)
{
    const std::filesystem::path oldPath = CreateAssetPath(assetNode);
    const std::string parentPath = CreateFolderPath(newParent);
    const std::filesystem::path newPath = parentPath + assetNode->GetName();

    if (!MoveFileEx(oldPath.c_str(), newPath.c_str(), MOVEFILE_WRITE_THROUGH))
    {
        AssetModificationResult assetResult = { false, nullptr, std::string(
            "MoveFileEx failed with error %d\n", GetLastError())
        };

        ErrorLogger::Log(Warning, assetResult.error);
        return assetResult;
    }

    return { true, assetNode };
}

FolderModificationResult AssetService::RenameFolder(FolderNode* folderNode, std::string newName)
{
    std::filesystem::path oldPath = CreateFolderPath(folderNode);
    std::string newPath = oldPath.parent_path().string() + "/" + newName;

    if (rename(oldPath.string().c_str(), newPath.c_str()) == 0)
        return { true, folderNode };

    return { false, nullptr, "Rename error" };
}

AssetModificationResult AssetService::RenameAsset(AssetNode* assetNode, std::string newName)
{
    std::filesystem::path oldPath = CreateAssetPath(assetNode);
    std::string newPath = oldPath.parent_path().string() + "/" + newName + oldPath.extension().string();
        
    if (rename(oldPath.string().c_str(), newPath.c_str()) == 0)
        return { true, assetNode };
    
    return { false, nullptr, "Rename error" };    
}

AssetTree* AssetService::CreateDebugAssetTree()
{
    AssetTree* assetTree = new AssetTree("Content");

    // First layer
    assetTree->CreateAssetNode(nullptr, "Asset11", assetTree->GetRootNode());
    assetTree->CreateAssetNode(nullptr, "Asset12", assetTree->GetRootNode());
    FolderNode* folder1 = assetTree->CreateFolderNode("Folder1", assetTree->GetRootNode()).node;

    // Second layer
    assetTree->CreateAssetNode(nullptr, "Asset21", folder1);
    FolderNode* folder21 = assetTree->CreateFolderNode("Folder21", folder1).node;
    FolderNode* folder22 = assetTree->CreateFolderNode("Folder22", folder1).node;

    // Third layer
    assetTree->CreateAssetNode(nullptr, "Asset311", folder21);
    assetTree->CreateAssetNode(nullptr, "Asset312", folder21);

    assetTree->CreateAssetNode(nullptr, "Asset321", folder22);
    assetTree->CreateAssetNode(nullptr, "Asset322", folder22);

    return assetTree;
}

void AssetService::SerializeToFile(Serializable* serializable, std::filesystem::path pathToFile)
{
    Json j;
    j = serializable->toJson();

    std::ofstream file(pathToFile);
    file << std::setw(4) << j << std::endl;
}

void AssetService::createSerializable(Serializable* serializable, std::filesystem::path pathToFile)
{
    checkFolderExist(pathToFile);
    if (!exists(pathToFile))
    {
        SerializeToFile(serializable, pathToFile);
        return;
    }

    std::ifstream file(pathToFile);
    Json json;
    file >> json;
    serializable->fromJson(json);
}

bool AssetService::checkFolderExist(std::filesystem::path fileRelativePath)
{
    if (exists(fileRelativePath.parent_path()))
        return false;

    create_directories(fileRelativePath.parent_path());
    return true;
}

