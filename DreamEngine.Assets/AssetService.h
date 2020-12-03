#pragma once

#include <filesystem>

#include "AssetTree.h"

class Serializer;

class AssetService
{

public:

    AssetService() = delete;

    inline static const std::string ASSET_FILE_EXTENSION = ".asset";

    static void CreateAssetFile(AssetNode* node);
    static void RemoveAssetFile(AssetNode* node);

    static AssetTree* FindAssetTree(std::string rootNodeName);

    static std::string CreateFolder(FolderNode* folderNode);
    static void CheckFolderExist(std::filesystem::path fileRelativePath);
    static FolderModificationResult RemoveFolder(FolderNode* folderNode, bool isRecursive);

    static std::string CreateFolderPath(FolderNode* folderNode);
    static std::string CreateAssetPath(AssetNode* assetNode);

    static FolderModificationResult MoveFolder(FolderNode* folderNode, FolderNode* newParent);
    static AssetModificationResult MoveAsset(AssetNode* assetNode, FolderNode* newParent);

    static AssetTree* CreateDebugAssetTree();

    template <class T = Serializer>
    static T* DeserializeActor(std::filesystem::path pathToConfig)
    {
        T* actor = new T();
        actor = static_cast<T*>(createSerializerActor(actor, pathToConfig));
        return actor;
    }

    static void SerializeActor(Serializer* actor, std::filesystem::path pathToConfig);

private:

    static Serializer* createSerializerActor(Serializer* actor, std::filesystem::path pathToConfig);
};
