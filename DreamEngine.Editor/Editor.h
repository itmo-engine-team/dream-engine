#pragma once

#include <vector>

#include "EditorWindow.h"
#include "EditorContext.h"

class Graphics;
class AssetManager;

class Editor
{

public:

    Editor(EditorContext* context);
    ~Editor();

    void Update();
    void Render();

    void AddDynamicWindow(EditorWindow* window);

    std::wstring GetEditorProjectPath() const;
    std::wstring GetPathFromEditor(std::wstring path) const;

    EditorContext* GetContext() const;

private:

    std::wstring editorProjectPath;

    EditorContext* context;

    std::vector<EditorWindow*> windows;
    std::vector<EditorWindow*> dynamicWindows;

    void initImGui();
    void startImGuiFrame();
    void finishImGuiFrame();

    void updateWindows();
    void renderWindows();
    void renderMainEditorMenu();

};

