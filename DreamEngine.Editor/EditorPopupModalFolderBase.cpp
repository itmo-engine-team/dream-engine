#include "EditorPopupModalFolderBase.h"

EditorPopupModalFolderBase::EditorPopupModalFolderBase(std::string name, FolderNode* parentFolderNode)
    : EditorPopupModal(std::move(name)), parentFolderNode(parentFolderNode)
{

}

FolderNode* EditorPopupModalFolderBase::GetFolderNode() const
{
    return parentFolderNode;
}
