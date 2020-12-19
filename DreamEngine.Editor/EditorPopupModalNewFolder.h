#pragma once

#include "EditorPopupModalFolderBase.h"

class FolderNode;

class EditorPopupModalNewFolder : public EditorPopupModalFolderBase
{
public:

    EditorPopupModalNewFolder(FolderNode* parentFolderNode);

    std::string GetFolderName();

protected:

    std::string folderNamePublic;

    void onDrawPopup() override;
    bool onFinish() override;

};

