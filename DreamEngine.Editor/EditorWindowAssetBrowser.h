#pragma once

#include "EditorWindow.h"
#include "Texture.h"
#include "AssetTree.h"
#include "AssetService.h"

class EditorWindowAssetBrowser : public EditorWindow
{

public:

    EditorWindowAssetBrowser(Editor* editor);

    void Update() override;
    void Render() override;

private:

    AssetTree* assetTree;

    FolderNode* currentParentNode = nullptr;

    Texture* iconFolder;
    Texture* iconFile;
    Texture* iconFilter;
    Texture* iconAsset;

    const char* fileNames[];
    
    void drawFilter();
    void drawPopupContextMenu();
    void drawPopupModalWindow();
    void drawFolderLayout(FolderNode* parentNode);
    void drawCommandMenu();
    void drawChildrenFolders(FolderNode* parentNode);
    void drawChildrenAssets(FolderNode* parentNode);

};

