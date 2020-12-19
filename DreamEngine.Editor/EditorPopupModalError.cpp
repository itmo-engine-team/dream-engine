#include "EditorPopupModalError.h"

#include "imgui.h"

EditorPopupModalError::EditorPopupModalError(std::string resultText)
    : EditorPopupModal("Error!")
{
    errorText = resultText;
}

void EditorPopupModalError::onDrawPopup()
{
    ImGui::Text(errorText.c_str());
}
