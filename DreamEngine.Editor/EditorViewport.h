#pragma once

#include "imgui.h"

class EditorViewport
{

public:

    EditorViewport(ImVec2 viewportRatio = ImVec2(16, 9));

    void UpdateSize();
    ImVec2 GetSize() const;

private:

    ImVec2 viewportRatio;
    ImVec2 viewportSize;
    float viewportSizeMultiplier = 20;

};

