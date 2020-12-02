#pragma once

#include "EditorWindow.h"

class EditorWindowGameViewport : public EditorWindow
{

public:

    EditorWindowGameViewport(Editor* editor);

    void Update() override;
    void Render() override;

};

