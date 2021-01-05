#pragma once

#include <vector>
#include <map>

#include "EditorWindow.h"
#include "EditorContext.h"
#include "Texture.h"
#include "AssetType.h"

class Graphics;
class AssetManager;

class Editor
{

public:

    Editor(EditorContext* context);
    ~Editor();

    void Update();
    void Render();

    bool AddDynamicWindow(EditorWindow* window);

    std::wstring GetEditorProjectPath() const;
    std::wstring GetPathFromEditor(std::wstring path) const;

    Texture* GetIconByAssetType(AssetType type) const;

    EditorContext* GetContext() const;

private:

    std::wstring EDITOR_PROJECT_PATH;
    std::map<AssetType, Texture*> MAP_ASSET_TYPE_TO_TEXTURE;

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

