#pragma once

#include "EditorPopupModalFolderBase.h"

class FolderNode;

class EditorPopupModalDeleteFolder : public EditorPopupModalFolderBase
{
public:

    EditorPopupModalDeleteFolder(FolderNode* parentFolderNode);
    bool GetIsRecursive();

protected:

    bool isRecursive = false;

    void onDrawPopup() override;

};


