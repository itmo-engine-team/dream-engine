#pragma once

#include "EditorWindow.h"

class EditorWindowGameViewport : public EditorWindow
{

public:

    EditorWindowGameViewport(Graphics* graphics);

    void Update() override;
    void Render() override;

};

