#include "AssetManager.h"

#include <queue>
#include "Libraries/id.hpp"

#include "AssetService.h"
#include "ErrorLogger.h"
#include "AssetInfoFactory.h"

AssetManager::AssetManager()
{
    if (isDebugTree)
        contentAssetTree = AssetService::CreateDebugAssetTree();
    else
        contentAssetTree = AssetService::FindAssetTree("Content");

    initAssetTree(contentAssetTree);
}

AssetManager::~AssetManager()
{
    delete contentAssetTree;
}

AssetModificationResult AssetManager::CreateAsset(
    AssetType assetType, const std::string& assetName, FolderNode* parentFolderNode)
{
    AssetInfo* assetInfo = AssetInfoFactory::Create(assetType);
    assetInfo->SetName(assetName);

    return addNewAsset(assetInfo, parentFolderNode);
}

AssetModificationResult AssetManager::RemoveAsset(AssetNode* assetNode)
{
    if (isDebugTree)
    {
        contentAssetTree->RemoveAssetNode(assetNode);
        delete assetNode;
        return { true, nullptr };
    }
    
    AssetModificationResult result = AssetService::RemoveAssetFile(assetNode);
    if (!result.isSuccess)
        return { false, assetNode };

    contentAssetTree->RemoveAssetNode(assetNode);
    delete assetNode;
    return { true, nullptr };
}

AssetModificationResult AssetManager::RenameAsset(AssetNode* assetNode, const std::string& newName)
{
    for (auto neighborAssetNode : assetNode->GetParent()->GetChildAssetList())
    {
        if (neighborAssetNode->GetName() == newName)
            return { false, assetNode, "This name is already exist in folder" };
    }

    if (isDebugTree)
    {
        contentAssetTree->RenameAssetNode(assetNode, newName);
        return { true, assetNode };
    }

    AssetModificationResult result = AssetService::RenameAsset(assetNode, newName);
    if (!result.isSuccess)
        return result;

    contentAssetTree->RenameAssetNode(assetNode, newName);
    return { true, assetNode };
}

AssetModificationResult AssetManager::DuplicateAsset(AssetNode* assetNode, const std::string& newName)
{
    AssetInfo* originalInfo = assetNode->GetAssetInfo();
    AssetInfo* duplicateAssetInfo = AssetInfoFactory::Duplicate(*originalInfo);
    duplicateAssetInfo->SetName(newName);

    AssetModificationResult result = addNewAsset(duplicateAssetInfo, assetNode->GetParent());
    return result;
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
    AssetModificationResult result = AssetService::SaveAsset(assetNode);
    return result;
}

FolderModificationResult AssetManager::CreateFolder(const std::string& assetName, FolderNode* parentFolderNode)
{
    FolderModificationResult result = contentAssetTree->CreateFolderNode(assetName, parentFolderNode);

    if (isDebugTree)
        return result;

    if (result.isSuccess)
    {
        FolderNode* folderNode = result.node;
        result = AssetService::CreateFolder(folderNode);
        if (!result.isSuccess)
        {
            contentAssetTree->RemoveFolderNode(folderNode, true);
        }

        return result;
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
    for (auto neighborFolderNode : folderNode->GetParent()->GetChildFolderList())
    {
        if (neighborFolderNode->GetName() == newName)
            return { false, folderNode, "Folder with this name is already exist" };
    }

    if (isDebugTree)
    {
        contentAssetTree->RenameFolderNode(folderNode, newName);
        return { true, folderNode };
    }

    FolderModificationResult result = AssetService::RenameFolder(folderNode, newName);
    if (!result.isSuccess)
        return result;

    contentAssetTree->RenameFolderNode(folderNode, newName);
    return { true, folderNode };
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

AssetModificationResult AssetManager::addNewAsset(AssetInfo* assetInfo, FolderNode* parentFolderNode)
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
        delete assetInfo;
        assetInfo = nullptr;

        return { false, nullptr, "Error while generating id for new asset" };
    }

    AssetModificationResult result = contentAssetTree->CreateAssetNode(
        assetInfo, assetInfo->GetName(), parentFolderNode);
    if (!result.isSuccess)
    {
        idSet.erase(newId);
        delete assetInfo;
        assetInfo = nullptr;

        return result;
    }

    if (!isDebugTree)
    {
        AssetNode* assetNode = result.node;
        result = AssetService::CreateAssetFile(assetNode);

        if (!result.isSuccess)
        {
            idSet.erase(newId);
            delete assetInfo;
            assetInfo = nullptr;

            contentAssetTree->RemoveAssetNode(assetNode);
        }
    }

    return result;
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
