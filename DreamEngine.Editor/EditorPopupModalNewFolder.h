#pragma once

#include "EditorPopupModal.h"

class EditorPopupModalNewFolder : public EditorPopupModal
{
public:

    EditorPopupModalNewFolder(std::string name);

    std::string GetFolderName();

protected:

    std::string folderNamePublic;

    void onDrawPopup() override;
    bool onFinish() override;


};

