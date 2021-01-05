#pragma once

#include "EditorWindow.h"

class EditorWindowShadowViewport : public EditorWindow
{

public:

    EditorWindowShadowViewport(Editor* editor);

    void Update() override;
    void Render() override;

};

