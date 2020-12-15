#include "EditorPopupModalDelete.h"

#include "imgui.h"

EditorPopupModalDelete::EditorPopupModalDelete(std::string name)
    : EditorPopupModal(name)
{

}

void EditorPopupModalDelete::onDrawPopup()
{
    ImGui::Text("This operation cannot be undone!");
}
