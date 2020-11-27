#include "EditorWindow.h"

EditorWindow::EditorWindow(std::string name) : name(std::move(name))
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
