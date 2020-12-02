#pragma once

#include <string>

class Editor;

class EditorWindow
{

public:

    EditorWindow(std::string name, Editor* editor);
    virtual ~EditorWindow() = default;

    virtual void Update() = 0;
    virtual void Render() = 0;

    std::string GetName() const;

    bool IsVisible() const;
    void SetVisible(bool isVisible);

protected:

    Editor* editor;

private:

    std::string name;

    bool isVisible = true;

};

