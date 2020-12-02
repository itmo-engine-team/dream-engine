#pragma once

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

    std::wstring GetEditorProjectPath() const;
    std::wstring GetPathFromEditor(std::wstring path) const;

    Graphics* GetGraphics() const;

private:

    std::wstring editorProjectPath;

    Graphics* graphics;
    std::vector<EditorWindow*> windows;

    void initImGui();
    void startImGuiFrame();
    void finishImGuiFrame();

    void updateWindows();
    void renderWindows();
    void renderMainEditorMenu();

};

