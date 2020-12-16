#pragma once

#include "EditorPopupModal.h"
#include "AssetInfoFactory.h"
#include <string>

class EditorPopupModalDelete : public EditorPopupModal
{
public:

    EditorPopupModalDelete(std::string name, bool isFolder);
    bool GetIsRecursive();

protected:

    std::string text;
    bool checkIsFolder;
    bool isRecursive = false;

    void onDrawPopup() override;

};


