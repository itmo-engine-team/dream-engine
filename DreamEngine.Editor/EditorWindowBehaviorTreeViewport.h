#pragma once
#include "EditorWindow.h"

class EditorWindowBehaviorTreeViewport : public EditorWindow
{

public:

    EditorWindowBehaviorTreeViewport(Editor* editor);

    void Update() override;
    void Render() override;

private:
    
    int nodeId;

    void beginDrawEditor();
    void drawSequence();
    void endDrawEditor();

};

