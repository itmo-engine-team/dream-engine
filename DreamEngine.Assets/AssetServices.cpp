#include "AssetServices.h"

#include <iomanip>

#include "ErrorLogger.h"

json AssetServices::CreateAssetFile(AssetNode* node)
{
    json j;

    const std::string pathVar(CreateAssetPath(node));

    CheckAndCreateFolder(pathVar);

    j["Object name"] = node->GetName();

    std::ofstream file(pathVar);
    file << std::setw(4) << j << std::endl;

    return j;
}

void AssetServices::RemoveAssetFile(AssetNode* node)
{
    const std::filesystem::path pathVar(CreateAssetPath(node));
    try
    {
        remove(pathVar);
    }
    catch (std::exception& e)
    {
        std::string error = std::string("Remove asset error. Extension: ") + e.what();
        ErrorLogger::Log(Warning, error);
    }
}

AssetTree* AssetServices::FindAssetTree()
{
    const std::string directoryName = "Content";
    const std::string extension = ".asset";

    AssetTree* assetTree = &AssetTree::GetInstance();
    assetTree->ClearAssetTree();

    std::vector<FolderNode*> foldersQueue;
    foldersQueue.push_back(assetTree->GetRootNode());

    while (!foldersQueue.empty())
    {
        FolderNode* currentFolderNode = foldersQueue.at(0);
        foldersQueue.erase(foldersQueue.begin());

        std::filesystem::directory_iterator endItr;
        for (std::filesystem::directory_iterator itr(directoryName); itr != endItr; ++itr)
        {
            if (is_directory(itr->status()))
            {
                FolderNode* childFolderNode = assetTree->CreateFolderNode(
                    itr->path().filename().string(), currentFolderNode);
                foldersQueue.push_back(childFolderNode);
            }
            else
            {
                if (itr->path().extension() != extension) continue;

                // TODO implement converting json file to AssetInfo
                AssetInfo* assetInfo = nullptr;

                assetTree->CreateAssetNode(
                    assetInfo, itr->path().filename().string(), currentFolderNode);
            }
        }
    }
    return assetTree;
}

void AssetServices::RemoveFolder(FolderNode* folderNode, const bool isRecursive)
{
    const std::filesystem::path pathVar(CreateFolderPath(folderNode));

    if (isRecursive)
        remove_all(pathVar);
    else
        remove(pathVar);
}

std::string AssetServices::CreateFolderPath(FolderNode* folderNode)
{
    std::string path;
    FolderNode* currentNode = folderNode;

    while (currentNode != nullptr)
    {
        path = currentNode->GetName() + "/" + path;
        currentNode = currentNode->GetParent();
    }

    return path;
}

std::string AssetServices::CreateAssetPath(AssetNode* assetNode)
{
    std::string path = CreateFolderPath(assetNode->GetParent()) +
        "/" + assetNode->GetName() + ".asset";

    return path;
}


void AssetServices::CheckAndCreateFolder(std::filesystem::path fileRelativePath)
{
    if (!exists(fileRelativePath.parent_path()))
        create_directories(fileRelativePath.parent_path());
}

