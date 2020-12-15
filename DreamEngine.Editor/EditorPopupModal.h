#pragma once

#include <string>

class EditorPopupModal
{

public:

    // Return true if popup is finished
    static bool DrawPipeline(EditorPopupModal* popup);

    EditorPopupModal(std::string name);
    virtual ~EditorPopupModal() = default;

    bool IsFinished() const;
    bool GetResult() const;
    
    void Draw();

protected:

    std::string name;

    bool isStarted = false;
    bool isFinished = false;
    bool result = false; // Shows if OK button was clicked 

    void finish(bool isSuccess);

    virtual bool onFinish() { return true; }
    virtual void onDrawPopup() = 0;

};

