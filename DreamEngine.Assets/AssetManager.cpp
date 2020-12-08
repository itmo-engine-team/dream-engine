#include "AssetManager.h"

#include <queue>
#include "Libraries/id.hpp"

#include "AssetService.h"
#include "ErrorLogger.h"

AssetManager::AssetManager()
{
    if (isDebugTree)
        contentAssetTree = AssetService::FindAssetTree("Content");
    else
        contentAssetTree = AssetService::CreateDebugAssetTree();

    initAssetTree(contentAssetTree);
}

AssetManager::~AssetManager()
{
    delete contentAssetTree;
}

AssetModificationResult AssetManager::AddNewAsset(
    AssetInfo* assetInfo, const std::string& assetName, FolderNode* parentFolderNode)
{
    // Generate id
    const auto newId = generateNewId();
    idSet.insert(newId);
    assetInfo->setId(newId);

    // Add asset to map
    const bool isAddedToMap = addAssetInfoToMap(assetInfo);
    if (!isAddedToMap)
    {
        idSet.erase(newId);
        assetInfo->setId(0);

        return { false, nullptr, "Error while generating id for new asset" };
    }
    
    AssetModificationResult result = contentAssetTree->CreateAssetNode(assetInfo, assetName, parentFolderNode);
    if (!result.isSuccess)
        return result;

    if (!isDebugTree)
    {
        // TODO Method must return result of operation
        AssetService::CreateAssetFile(result.node);
    }

    return result;
}

AssetModificationResult AssetManager::RemoveAsset(AssetNode* assetNode)
{
    if (isDebugTree)
    {
        contentAssetTree->RemoveAssetNode(assetNode);
        return { true, nullptr };
    }

    // TODO Method must return result of operation
    AssetService::RemoveAssetFile(assetNode);
    contentAssetTree->RemoveAssetNode(assetNode);
    return { true, nullptr };
}

AssetModificationResult AssetManager::RenameAsset(AssetNode* assetNode, const std::string& newName)
{
    // TODO
    return { false, assetNode, "Not Implemented Yet" };
}

AssetModificationResult AssetManager::DuplicateAsset(AssetNode* assetNode)
{
    // TODO
    return { false, assetNode, "Not Implemented Yet" };
}

AssetModificationResult AssetManager::MoveAsset(AssetNode* assetNode, FolderNode* newParentFolderNode)
{
    // Check for equal names
    for (AssetNode* newNeighborAssetNode : newParentFolderNode->GetChildAssetList())
    {
        if (assetNode->GetName() == newNeighborAssetNode->GetName())
            return { false, assetNode,
                assetNode->GetName() + " asset is already exist in new folder" };
    }

    if (isDebugTree)
    {
        contentAssetTree->MoveAssetNode(assetNode, newParentFolderNode);
        return { true, assetNode };
    }

    // Move asset
    AssetModificationResult result = AssetService::MoveAsset(assetNode, newParentFolderNode);
    if (result.isSuccess)
        contentAssetTree->MoveAssetNode(assetNode, newParentFolderNode);

    return result;
}

AssetModificationResult AssetManager::SaveAsset(AssetNode* assetNode)
{
    // TODO
    return { false, assetNode, "Not Implemented Yet" };
}

FolderModificationResult AssetManager::CreateFolder(const std::string& assetName, FolderNode* parentFolderNode)
{
    FolderModificationResult result = contentAssetTree->CreateFolderNode(assetName, parentFolderNode);

    if (isDebugTree)
        return result;

    if (result.isSuccess)
    {
        // TODO Method must return result of operation
        AssetService::CreateFolder(result.node);
    }

    return result;
}

FolderModificationResult AssetManager::RemoveFolder(FolderNode* folderNode, bool isRecursive)
{
    if (isDebugTree)
    {
        contentAssetTree->RemoveFolderNode(folderNode, isRecursive);
        return { true, nullptr };
    }

    FolderModificationResult result = AssetService::RemoveFolder(folderNode, isRecursive);
    if (result.isSuccess)
        contentAssetTree->RemoveFolderNode(folderNode, isRecursive);

    return result;
}

FolderModificationResult AssetManager::RenameFolder(FolderNode* folderNode, const std::string& newName)
{
    // TODO
    return { false, folderNode, "Not Implemented Yet" };
}

FolderModificationResult AssetManager::MoveFolder(FolderNode* folderNode, FolderNode* newParentFolderNode)
{
    for (FolderNode* neighborFolderNode : newParentFolderNode->GetChildFolderList())
    {
        if (folderNode->GetName() == neighborFolderNode->GetName())
            return { false, folderNode,
                folderNode->GetName() + " folder is already exist in new place" };
    }

    if (isDebugTree)
    {
        contentAssetTree->MoveFolderNode(folderNode, newParentFolderNode);
        return { true, nullptr };
    }

    FolderModificationResult result = AssetService::MoveFolder(folderNode, newParentFolderNode);
    if (result.isSuccess)
        contentAssetTree->MoveFolderNode(folderNode, newParentFolderNode);
    return result;
}

AssetTree* AssetManager::GetContentAssetTree() const
{
    return contentAssetTree;
}

void AssetManager::initAssetTree(AssetTree* assetTree)
{
    std::queue<FolderNode*> folderQueue;
    folderQueue.push(assetTree->GetRootNode());
    
    FolderNode* currentFolderNode = nullptr;
    while (!folderQueue.empty())
    {
        currentFolderNode = folderQueue.front();
        folderQueue.pop();

        for (AssetNode* assetNode : currentFolderNode->GetChildAssetList())
        {
            if (assetNode->GetAssetInfo() != nullptr)
            {
                addAssetInfoToMap(assetNode->GetAssetInfo());
            }
            else
            {
                ErrorLogger::Log(Error,
                    "AssetInfo is null for AssetNode with name " + assetNode->GetName());
            }
        }

        for (FolderNode* folderNode : currentFolderNode->GetChildFolderList())
        {
            folderQueue.push(folderNode);
        }
    }
}

bool AssetManager::addAssetInfoToMap(AssetInfo* assetInfo)
{
    if (assetMap.find(assetInfo->GetId()) != assetMap.end()) return false;

    assetMap[assetInfo->GetId()] = assetInfo;
    return true;
}

unsigned int AssetManager::generateNewId() const
{
    const unsigned int newId = $ID();

    return newId > 0 && idSet.find(newId) == idSet.end() ? newId : generateNewId();
}
