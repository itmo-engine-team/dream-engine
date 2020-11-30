#pragma once

#include "EditorWindow.h"
#include "Texture.h"

class EditorWindowAssetBrowser : public EditorWindow
{

public:

    EditorWindowAssetBrowser(Graphics* graphics);

    void Update() override;
    void Render() override;

    

private:

    Texture* iconFolder;
    Texture* iconFile;
    Texture* iconFilter;

    bool layoutChange;
    const char* fileNames[];
    
    void popupContextMenu();
    void fileLayout();
    void folderLayout();
};

