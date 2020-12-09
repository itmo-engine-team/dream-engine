#include "pch.h"

#include "AssetService.h"
#include "EngineConfigInfo.h"

TEST(AssetTest, CreateAsset)
{
    AssetTree* assetTree = AssetService::FindAssetTree("Content");
    AssetModificationResult assetResult = assetTree->CreateAssetNode(nullptr, "Person", assetTree->GetRootNode());

    if (assetResult.isSuccess)
        AssetService::CreateAssetFile(assetResult.node);
    else
        printf(assetResult.error.c_str());
}

TEST(AssetTest, RemoveAsset)
{
    AssetTree* assetTree = AssetService::FindAssetTree("Content");

    AssetService::RemoveAssetFile(assetTree->GetRootNode()->GetChildAssetList()[0]);
    assetTree->RemoveAssetNode(assetTree->GetRootNode()->GetChildAssetList()[0]);
}

TEST(AssetTest, CreateFolders)
{
    AssetTree* assetTree = AssetService::FindAssetTree("Content");

    // First layer
    FolderModificationResult folderResult = assetTree->CreateFolderNode("Folder1", assetTree->GetRootNode());
    if (folderResult.isSuccess)
    {
        AssetService::CreateFolder(folderResult.node);
    }
    else
    {
        printf(folderResult.error.c_str());
        return;
    }

    AssetModificationResult assetResult = assetTree->CreateAssetNode(nullptr, "Person1.1", folderResult.node);
    if (assetResult.isSuccess)
        AssetService::CreateAssetFile(assetResult.node);
    else
        printf(assetResult.error.c_str());

    assetResult = assetTree->CreateAssetNode(nullptr, "Person1.2", folderResult.node);
    if (assetResult.isSuccess)
        AssetService::CreateAssetFile(assetResult.node);
    else
        printf(assetResult.error.c_str());

    // Second Layer
    folderResult = assetTree->CreateFolderNode("Folder2", assetTree->GetRootNode()->GetChildFolderList()[0]);
    if (folderResult.isSuccess)
    {
        AssetService::CreateFolder(folderResult.node);
    }
    else
    {
        printf(folderResult.error.c_str());
        return;
    }

    assetResult = assetTree->CreateAssetNode(nullptr, "Person2.1", folderResult.node);
    if (assetResult.isSuccess)
        AssetService::CreateAssetFile(assetResult.node);
    else
        printf(assetResult.error.c_str());

    assetResult = assetTree->CreateAssetNode(nullptr, "Person2.2", folderResult.node);
    if (assetResult.isSuccess)
        AssetService::CreateAssetFile(assetResult.node);
    else
        printf(assetResult.error.c_str());

    // Third Layer

    folderResult = assetTree->CreateFolderNode("Folder3.1", assetTree->GetRootNode()->GetChildFolderList()[0]->GetChildFolderList()[0]);
    if (folderResult.isSuccess)
    {
        AssetService::CreateFolder(folderResult.node);
    }
    else
    {
        printf(folderResult.error.c_str());
        return;
    }

    assetResult = assetTree->CreateAssetNode(nullptr, "Person3.1", folderResult.node);
    if (assetResult.isSuccess)
        AssetService::CreateAssetFile(assetResult.node);
    else
        printf(assetResult.error.c_str());

    folderResult = assetTree->CreateFolderNode("Folder3.2", assetTree->GetRootNode()->GetChildFolderList()[0]->GetChildFolderList()[0]);
    if (assetResult.isSuccess)
    {
        AssetService::CreateFolder(folderResult.node);
    }
    else
    {
        printf(folderResult.error.c_str());
        return;
    }

    assetResult = assetTree->CreateAssetNode(nullptr, "Person3.2", folderResult.node);
    if (assetResult.isSuccess)
        AssetService::CreateAssetFile(assetResult.node);
    else
        printf(assetResult.error.c_str());
}

TEST(AssetTest, RecursiveRemoveFolder)
{
    AssetTree* assetTree = AssetService::FindAssetTree("Content");

    FolderNode* folderNode = assetTree->GetRootNode()->GetChildFolderList()[0];

    AssetService::RemoveFolder(folderNode, true);
    assetTree->RemoveFolderNode(folderNode, true);
}

TEST(AssetTest, NoRecursiveRemoveFolder)
{
    AssetTree* assetTree = AssetService::FindAssetTree("Content");

    FolderNode* folderNode = assetTree->GetRootNode()->GetChildFolderList()[0];

    FolderModificationResult folderResult = AssetService::RemoveFolder(folderNode, false);
    if (folderResult.isSuccess)
        assetTree->RemoveFolderNode(folderNode, false);
    else
        printf(folderResult.error.c_str());
}

TEST(AssetTest, MoveFolder)
{
    AssetTree* assetTree = AssetService::FindAssetTree("Content");

    FolderNode* folderNode = assetTree->GetRootNode()->GetChildFolderList()[0]->GetChildFolderList()[0];

    FolderModificationResult folderResult = AssetService::MoveFolder(folderNode, assetTree->GetRootNode());
    if (folderResult.isSuccess)
        assetTree->MoveFolderNode(folderNode, assetTree->GetRootNode());
    else
        printf(folderResult.error.c_str());
}

TEST(AssetTest, MoveAsset)
{
    AssetTree* assetTree = AssetService::FindAssetTree("Content");

    AssetNode* assetNode = assetTree->GetRootNode()->GetChildFolderList()[0]->GetChildAssetList()[0];

    AssetModificationResult assetResult = AssetService::MoveAsset(assetNode, assetTree->GetRootNode());
    if (assetResult.isSuccess)
        assetTree->MoveAssetNode(assetNode, assetTree->GetRootNode());
    else
        printf(assetResult.error.c_str());
}

TEST(AssetTest, ImportFromFile)
{
    EngineConfigInfo* test = AssetService::DeserializeFromFile<EngineConfigInfo>("Content/EngineConfig.json");
    std::cout << test->IsGameMode();
}

TEST(AssetTest, SaveEngineConfig)
{
    EngineConfigInfo* test = new EngineConfigInfo();
    AssetService::SerializeToFile(test, "Content/EngineConfig.json");
    std::cout << test->IsGameMode();
}

TEST(AssetTest, RenameAsset)
{
    AssetTree* assetTree = AssetService::FindAssetTree("Content");
    AssetNode* assetNode = assetTree->GetRootNode()->GetChildFolderList()[0]->GetChildAssetList()[1];

    std::string newName = "Person1.12";
    AssetModificationResult assetResult = AssetService::RenameAsset(assetNode, newName);
    if (assetResult.isSuccess)
        assetTree->RenameAssetNode(assetNode, newName);
    else
        printf(assetResult.error.c_str());
}