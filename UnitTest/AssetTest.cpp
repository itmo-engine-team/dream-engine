#include "pch.h"

#include "AssetServices.h"

TEST(JsonTest, CreateAsset)
{
    AssetTree* assetTree = AssetServices::FindAssetTree("Content");
    AssetNode* assetNode = assetTree->CreateAssetNode(nullptr, "Person", assetTree->GetRootNode());
    AssetServices::CreateAssetFile(assetNode);

}

TEST(JsonTest, RemoveAsset)
{    
    AssetTree* assetTree = AssetServices::FindAssetTree("Content");

    AssetServices::RemoveAssetFile(assetTree->GetRootNode()->GetChildAssetList()[0]);
   assetTree->RemoveAssetNode(assetTree->GetRootNode()->GetChildAssetList()[0]);
}
