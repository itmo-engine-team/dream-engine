#pragma once
#include "EditorWindow.h"
class EditorWindowModelViewer : public EditorWindow 
{

public: 

    EditorWindowModelViewer(Editor* editor);

    void Update() override;
    void Render() override;

    bool GetResult();

private:

    bool result = false;

    void renderModelViewer();
    void renderModelInspector();

};

