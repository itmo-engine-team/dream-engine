#pragma once

#include <string>

class Graphics;

class EditorWindow
{

public:

    EditorWindow(std::string name, Graphics* graphics);
    virtual ~EditorWindow() = default;

    virtual void Update() = 0;
    virtual void Render() = 0;

    std::string GetName() const;

    bool IsVisible() const;
    void SetVisible(bool isVisible);

protected:

    Graphics* graphics;

private:

    std::string name;

    bool isVisible = true;

};

