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

    TreeModificationResult(bool isSuccess) : isSuccess(isSuccess), node(nullptr), error("") {}
    TreeModificationResult(T* node) : isSuccess(true), node(node), error("") {}
    TreeModificationResult(const std::string error) : isSuccess(false), node(nullptr), error(error) {}
};

struct AssetModificationResult : TreeModificationResult<AssetNode>
{
};

struct FolderModificationResult : TreeModificationResult<FolderNode>
{
};