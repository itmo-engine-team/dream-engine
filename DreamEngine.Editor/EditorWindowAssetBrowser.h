#pragma once

#include "EditorWindow.h"

class EditorWindowAssetBrowser : public EditorWindow
{

public:

    EditorWindowAssetBrowser(Graphics* graphics);

    void Update() override;
    void Render() override;

};

