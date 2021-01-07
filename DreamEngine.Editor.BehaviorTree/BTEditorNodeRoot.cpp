#include "BTEditorNodeRoot.h"

BTEditorNodeRoot::BTEditorNodeRoot() : BTEditorNode(BTNodeType::Root)
{
    setTypeName("Root");
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
