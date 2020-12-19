#pragma once

#include "EditorPopupModal.h"

class EditorPopupModalError : public EditorPopupModal
{
public:

    EditorPopupModalError(std::string resultText);

protected:

    std::string errorText;

    void onDrawPopup() override;

};

