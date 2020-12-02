#include "EditorWindow.h"

EditorWindow::EditorWindow(std::string name, Editor* editor)
    : name(std::move(name)), editor(editor)
{

}

std::string EditorWindow::GetName() const
{
    return name;
}

bool EditorWindow::IsVisible() const
{
    return isVisible;
}

void EditorWindow::SetVisible(const bool isVisible)
{
    this->isVisible = isVisible;
}
