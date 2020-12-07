#pragma once

#include <vector>

#include "EditorWindow.h"

class Graphics;
class AssetManager;

class Editor
{

public:

    Editor(Graphics* graphics, AssetManager* assetManager);
    ~Editor();

    void Update();
    void Render();

    std::wstring GetEditorProjectPath() const;
    std::wstring GetPathFromEditor(std::wstring path) const;

    Graphics* GetGraphics() const;
    AssetManager* GetAssetManager() const;

private:

    std::wstring editorProjectPath;

    Graphics* graphics;
    AssetManager* assetManager;

    std::vector<EditorWindow*> windows;

    void initImGui();
    void startImGuiFrame();
    void finishImGuiFrame();

    void updateWindows();
    void renderWindows();
    void renderMainEditorMenu();

};

