#pragma once

#include "EditorWindow.h"

class EditorWindowShadowViewport : public EditorWindow
{

public:

    EditorWindowShadowViewport(Graphics* graphics);

    void Update() override;
    void Render() override;

};

