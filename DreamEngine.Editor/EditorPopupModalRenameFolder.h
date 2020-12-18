#pragma once

#include "EditorPopupModalFolderBase.h"

class FolderNode;

class EditorPopupModalRenameFolder : public EditorPopupModalFolderBase
{
public:

    EditorPopupModalRenameFolder(FolderNode* parentFolderNode);

    std::string GetNewFolderName();

protected:

    std::string newFolderName;

    void onDrawPopup() override;
    bool onFinish() override;
};

