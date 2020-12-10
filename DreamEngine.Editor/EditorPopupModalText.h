#pragma once

#include "EditorPopupModal.h"
#include <string>

class EditorPopupModalText : public EditorPopupModal
{

public:

    EditorPopupModalText(std::string name, std::string text);

protected:

    std::string text;

    void onDrawPopup() override;

};

