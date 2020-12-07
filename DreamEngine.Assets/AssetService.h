#pragma once

#include <filesystem>

#include "AssetTree.h"

class Serializable;

class AssetService
{

public:

    AssetService() = delete;

    inline static const std::string ASSET_FILE_EXTENSION = ".asset";

    static std::string CreateFolder(FolderNode* folderNode);
    static void CreateAssetFile(AssetNode* node);
 
    static FolderModificationResult RemoveFolder(FolderNode* folderNode, bool isRecursive);
    static void RemoveAssetFile(AssetNode* node);

    static std::string CreateFolderPath(FolderNode* folderNode);
    static std::string CreateAssetPath(AssetNode* assetNode);

    static FolderModificationResult MoveFolder(FolderNode* folderNode, FolderNode* newParent);
    static AssetModificationResult MoveAsset(AssetNode* assetNode, FolderNode* newParent);

    static FolderModificationResult RenameFolder(FolderNode* folderNode, std::string newName);
    static AssetModificationResult RenameAsset(AssetNode* assetNode, std::string newName);

    static AssetTree* CreateDebugAssetTree();

    static void CheckFolderExist(std::filesystem::path fileRelativePath);

    static AssetTree* FindAssetTree(std::string rootNodeName);

    static AssetModificationResult DuplicateAsset(AssetNode* assetNode, std::string& newNodeName);

    template <class T = Serializable>
    static T* DeserializeFromFile(std::filesystem::path pathToConfig)
    {
        T* serializable = new T();
        createSerializable(serializable, pathToConfig);
        return serializable;
    }

    static void SerializeToFile(Serializable* serializable, std::filesystem::path pathToFile);

private:

    static void createSerializable(Serializable* serializable, std::filesystem::path pathToFile);
};
