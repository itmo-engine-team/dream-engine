#pragma once

#include "EditorWindow.h"
#include "imgui.h"

class EditorWindowGameViewport : public EditorWindow
{

public:

    ImVec2 gameViewportSize = ImVec2(160, 90);

    EditorWindowGameViewport(Editor* editor);

    void Update() override;
    void Render() override;
    void renderGameEditorMenu();

};

