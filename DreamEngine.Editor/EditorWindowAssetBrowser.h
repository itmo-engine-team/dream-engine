#pragma once

#include "EditorWindow.h"
#include "Texture.h"
#include "AssetTree.h"
#include "AssetService.h"
#include "EditorPopupModalText.h"
#include "EditorPopupModalNewAsset.h"
#include "EditorPopupModalNewFolder.h"
#include "EditorPopupModalDeleteFolder.h"
#include "EditorPopupModalDeleteAsset.h"
#include "EditorPopupModalRenameFolder.h"
#include "EditorPopupModalDuplicateAsset.h"

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
    AssetNode* currentAssetNode = nullptr;

    Texture* iconFolder;
    Texture* iconFile;
    Texture* iconFilter;
    Texture* iconAsset;

    std::string assetPath;

    EditorPopupModalNewAsset* newAssetPopupModal;
    EditorPopupModalNewFolder* newFolderPopupModal;
    EditorPopupModalDeleteFolder* deleteFolderPopupModal;
    EditorPopupModalDeleteAsset* deleteAssetPopupModal;
    EditorPopupModalRenameFolder* renameFolderPopupModal;
    EditorPopupModalDuplicateAsset* duplicateAssetPopupModal;

    const char* fileNames[];
    
    void drawFilter();
    void drawFolderContextMenu(FolderNode* selectedFolderNode);
    void drawAssetContextMenu(AssetNode* selectedAssetNode);
    void drawFolderLayout(FolderNode* parentNode);
    void drawCommandMenu();
    void drawFolderTreeNode(FolderNode* folderNode, int level = 0);
    void drawFolderTreeNodePadding(int level);
    void drawChildrenAssets(FolderNode* parentNode);

    void drawNewAssetPopup();
    void drawNewFolderPopup();
    void drawDeleteFolderPopup();
    void drawDeleteAssetPopup();
    void drawRenameFolderPopup();
    void drawDuplicateAssetPopup();
    void drawPopups();

};