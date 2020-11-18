#include "pch.h"

#include "AssetServices.h"

TEST(JsonTest, CreateTest)
{   
    AssetServices::CreateAssetFile("Content/Person1.asset");
}

TEST(JsonTest, ReadTest)
{    
   // AssetServices::AssetReader
}

TEST(JsonTest, FindTest)
{
    AssetServices::FindAssets();
}