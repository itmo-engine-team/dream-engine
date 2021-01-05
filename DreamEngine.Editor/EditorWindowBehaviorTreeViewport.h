#pragma once
#include "EditorWindow.h"

class EditorWindowBehaviorTreeViewport : public EditorWindow
{

public:

    EditorWindowBehaviorTreeViewport(Editor* editor);

    void Init() override;
    void Update() override;
    void Render() override;

};

