#pragma once

#include "EditorWindow.h"
#include "Texture.h"
#include "AssetTree.h"
#include "AssetServices.h"

class EditorWindowAssetBrowser : public EditorWindow
{

public:

    EditorWindowAssetBrowser(Graphics* graphics);

    void Update() override;
    void Render() override;

private:

    AssetTree* assetTree;
    FolderNode* rootNode;
    FolderNode* currentParentNode = nullptr;

    Texture* iconFolder;
    Texture* iconFile;
    Texture* iconFilter;
    Texture* iconAsset;

    const char* fileNames[];
    
    void createFilter();
    void popupContextMenu();
    void folderLayout(FolderNode* parentNode);
    void createCommandMenu();
    void addTreeFolders(FolderNode* parentNode);
    void addTreeAssets(FolderNode* parentNode);

};

