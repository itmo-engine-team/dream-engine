#include "EditorWindow.h"

EditorWindow::EditorWindow(std::string name, Editor* editor)
    : name(std::move(name)), editor(editor)
{

}

std::string EditorWindow::GetName() const
{
    return name;
}

bool EditorWindow::IsOpened() const
{
    return isOpened;
}

void EditorWindow::SetOpened(const bool isOpened)
{
    this->isOpened = isOpened;
}
