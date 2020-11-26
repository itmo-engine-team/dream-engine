#pragma once

#include <string>

class EditorWindow
{

public:

    EditorWindow(std::string name);
    virtual ~EditorWindow() = default;

    virtual void Update() = 0;
    virtual void Render() = 0;

    std::string GetName() const;

    bool IsVisible() const;
    void SetVisible(bool isVisible);

private:

    std::string name;

    bool isVisible = true;

};

