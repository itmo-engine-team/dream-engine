#pragma once

#include <string>

class FolderNode;
class AssetNode;

template<class T>
struct TreeModificationResult
{
    bool isSuccess;
    T* node;
    std::string error;
    
    TreeModificationResult(bool isSuccess, T* node = nullptr, std::string error = "")
        : isSuccess(isSuccess), node(node), error(error) {}
};

struct AssetModificationResult : TreeModificationResult<AssetNode>
{
    AssetModificationResult(bool isSuccess, AssetNode* node = nullptr, std::string error = "")
        : TreeModificationResult<AssetNode>(isSuccess, node, error) {}
};

struct FolderModificationResult : TreeModificationResult<FolderNode>
{
    FolderModificationResult(bool isSuccess, FolderNode* node = nullptr, std::string error = "")
        : TreeModificationResult<FolderNode>(isSuccess, node, error) {}
};