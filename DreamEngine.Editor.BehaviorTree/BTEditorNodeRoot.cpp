#include "BTEditorNodeRoot.h"

BTEditorNodeRoot::BTEditorNodeRoot() : BTEditorNode(BTNodeType::Root)
{
    setName("Root");
}

bool BTEditorNodeRoot::CanHaveParent()
{
    return false;
}

bool BTEditorNodeRoot::CanHaveChild()
{
    return true;
}

bool BTEditorNodeRoot::CanHaveChildren()
{
    return false;
}
