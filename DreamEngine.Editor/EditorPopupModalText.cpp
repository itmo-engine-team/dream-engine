#include "EditorPopupModalText.h"

#include "imgui.h"

EditorPopupModalText::EditorPopupModalText(const std::string name, std::string text)
    : EditorPopupModal(name), text(std::move(text))
{

}

void EditorPopupModalText::onDrawPopup()
{
    ImGui::Text(text.data());
}
