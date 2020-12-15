#pragma once

#include <string>

class EditorPopupModal
{

public:

    EditorPopupModal(std::string name);
    virtual ~EditorPopupModal() = default;

    bool IsFinished() const;
    bool GetResult() const;
    
    void Draw();

protected:

    std::string name;

    bool isFinished = false;
    bool result = false;
    bool isStarted = false;

    void finish(bool isSuccess);

    virtual void onFinish() {}
    virtual void onDrawPopup() = 0;

};

