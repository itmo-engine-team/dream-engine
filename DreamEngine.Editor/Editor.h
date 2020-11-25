#pragma once

#include <d3d.h>
#include <vector>

#include "EditorWindow.h"

class Editor
{

public:

    Editor(HWND hWnd);
    ~Editor();

    void Update();
    void Render();

private:

    std::vector<EditorWindow*> windows;

    void initImGui(HWND hWnd);
    void startImGuiFrame();
    void finishImGuiFrame();

    void updateWindows();
    void renderWindows();

};

