#include "AssetManager.h"

#include <queue>
#include "Libraries/id.hpp"

#include "AssetService.h"
#include "ErrorLogger.h"

AssetManager::AssetManager()
{
    // TODO uncomment when ready to not use real folder structure
    // contentAssetTree = AssetServices::FindAssetTree("Content");
    contentAssetTree = AssetService::CreateDebugAssetTree();

    initAssetTree(contentAssetTree);
}

AssetManager::~AssetManager()
{
    delete contentAssetTree;
}

void AssetManager::AddNewAsset(AssetInfo* assetInfo, const std::string& assetName, FolderNode* parentFolderNode)
{
    const auto newId = generateNewId();
    idSet.insert(newId);
    assetInfo->setId(newId);

    addAssetInfoToMap(assetInfo);

    contentAssetTree->CreateAssetNode(assetInfo, assetName, parentFolderNode);
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

void AssetManager::addAssetInfoToMap(AssetInfo* assetInfo)
{
    assetMap[assetInfo->GetAssetType()][assetInfo->GetId()] = assetInfo;
}

unsigned int AssetManager::generateNewId() const
{
    const unsigned int newId = $ID();

    return idSet.find(newId) == idSet.end() ? newId : generateNewId();
}
