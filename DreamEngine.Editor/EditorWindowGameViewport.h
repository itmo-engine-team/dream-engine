#pragma once

#include "EditorWindow.h"

class EditorWindowGameViewport : public EditorWindow
{

public:

    EditorWindowGameViewport(std::string name);

    void Update() override;
    void Render() override;

};

