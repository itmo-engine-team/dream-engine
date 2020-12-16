#pragma once

#include "EditorPopupModal.h"
#include "AssetInfoFactory.h"
#include <string>

class EditorPopupModalDelete : public EditorPopupModal
{
public:

    EditorPopupModalDelete(std::string name);

protected:

    std::string text;

    void onDrawPopup() override;

};


