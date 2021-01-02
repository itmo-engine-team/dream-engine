#include "EditorViewport.h"

#include <algorithm>

EditorViewport::EditorViewport(ImVec2 viewportRatio)
    : viewportRatio(viewportRatio)
{

}

void EditorViewport::UpdateSize()
{
    const ImVec2 windowSize = ImGui::GetWindowSize();
    viewportSizeMultiplier = std::min(windowSize.x / viewportRatio.x, windowSize.y / viewportRatio.y);
    viewportSize = ImVec2(viewportRatio.x * viewportSizeMultiplier, viewportRatio.y * viewportSizeMultiplier);
}

ImVec2 EditorViewport::GetSize() const
{
    return viewportSize;
}
