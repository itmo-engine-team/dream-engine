#include "EditorWindow.h"

EditorWindow::EditorWindow(std::string name, Graphics* graphics)
    : name(std::move(name)), graphics(graphics)
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
