#pragma once

#include <d3d.h>
#include <d3d11.h>
#include <vector>

#include "EditorWindow.h"

class Editor
{

public:

    Editor(ID3D11Device* device, ID3D11DeviceContext* context, HWND hWnd);
    ~Editor();

    void Update();
    void Render();

private:

    std::vector<EditorWindow*> windows;

    void initImGui(ID3D11Device* device, ID3D11DeviceContext* context, HWND hWnd);
    void startImGuiFrame();
    void finishImGuiFrame();

    void updateWindows();
    void renderWindows();
    void renderMainEditorMenu();

};

