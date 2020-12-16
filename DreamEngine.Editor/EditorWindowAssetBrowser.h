#pragma once

#include "EditorWindow.h"
#include "Texture.h"
#include "AssetTree.h"
#include "AssetService.h"
#include "EditorPopupModalText.h"
#include "EditorPopupModalNewAsset.h"
#include "EditorPopupModalNewFolder.h"
#include "EditorPopupModalDelete.h"

class EditorWindowAssetBrowser : public EditorWindow
{

public:

    EditorWindowAssetBrowser(Editor* editor);

    void Update() override;
    void Render() override;

private:

    AssetTree* assetTree;
    AssetManager* assetManager;

    FolderNode* currentParentNode = nullptr;

    Texture* iconFolder;
    Texture* iconFile;
    Texture* iconFilter;
    Texture* iconAsset;

    std::string assetPath;

    EditorPopupModalNewAsset* newAssetPopupModal;
    EditorPopupModalNewFolder* newFolderPopupModal;
    EditorPopupModalDelete* deleteFolderPopupModal;

    const char* fileNames[];
    
    void drawFilter();
    void drawFolderContextMenu();
    void drawAssetContextMenu();
    void drawFolderLayout(FolderNode* parentNode);
    void drawCommandMenu();
    void drawChildrenFolders(FolderNode* parentNode);
    void drawChildrenAssets(FolderNode* parentNode);

    void drawNewAssetPopup();
    void drawNewFolderPopup();
    void drawDeletePopup();
    void drawPopups();

};