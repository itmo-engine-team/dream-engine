#pragma once
#include <map>

#include "EditorWindow.h"
#include "Texture.h"
#include "AssetTree.h"
#include "AssetService.h"
#include "EditorWindowModelViewer.h"
#include "EditorPopupModalText.h"
#include "EditorPopupModalNewAsset.h"
#include "EditorPopupModalNewFolder.h"
#include "EditorPopupModalDeleteFolder.h"
#include "EditorPopupModalDeleteAsset.h"
#include "EditorPopupModalRenameFolder.h"
#include "EditorPopupModalRenameAsset.h"
#include "EditorPopupModalDuplicateAsset.h"
#include "EditorPopupModalError.h"

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
    Texture* iconActor;
    Texture* iconScene;
    Texture* iconModel;
    Texture* iconTexture;
    Texture* iconBT;
    Texture* iconBP;

    std::string assetPath;

    EditorPopupModalNewAsset* newAssetPopupModal;
    EditorPopupModalNewFolder* newFolderPopupModal;
    EditorPopupModalDeleteFolder* deleteFolderPopupModal;
    EditorPopupModalDeleteAsset* deleteAssetPopupModal;
    EditorPopupModalRenameFolder* renameFolderPopupModal;
    EditorPopupModalRenameAsset* renameAssetPopupModal;
    EditorPopupModalDuplicateAsset* duplicateAssetPopupModal;
    EditorPopupModalError* errorPopupModal;

    const char* fileNames[];
    
    void setCurrentParentNode(FolderNode* currentParentNode);

    Texture* getAssetIconByNodeType(AssetNode* assetNode) const;

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
    void drawRenameAssetPopup();
    void drawDuplicateAssetPopup();
    void drawErrorPopup();
    void drawPopups();

};