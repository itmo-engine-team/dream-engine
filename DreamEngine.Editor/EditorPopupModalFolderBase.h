#pragma once

#include "EditorPopupModal.h"

class FolderNode;

class EditorPopupModalFolderBase : public EditorPopupModal
{

public:

    EditorPopupModalFolderBase(std::string name, FolderNode* parentFolderNode);

    FolderNode* GetFolderNode() const;

protected:

    FolderNode* parentFolderNode;

};

