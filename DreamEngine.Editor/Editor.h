#pragma once

#include <d3d.h>
#include <d3d11.h>
#include <vector>

#include "EditorWindow.h"

class Graphics;

class Editor
{

public:

    Editor(Graphics* graphics);
    ~Editor();

    void Update();
    void Render();

private:

    Graphics* graphics;
    std::vector<EditorWindow*> windows;

    void initImGui();
    void startImGuiFrame();
    void finishImGuiFrame();

    void updateWindows();
    void renderWindows();
    void renderMainEditorMenu();

};

