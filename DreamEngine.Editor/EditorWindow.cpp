#include "EditorWindow.h"

EditorWindow::EditorWindow(std::string name) : name(std::move(name))
{

}

std::string EditorWindow::GetName() const
{
    return name;
}
