#pragma once

#include "windows.h"

#include <bitset>
#include <queue>
#include <optional>

#include "InputSystemUtils.h"

class InputSystem
{

public:

    struct RawDelta
    {
        int x, y;
    };

    InputSystem() = default;
    ~InputSystem() = default;
    InputSystem(const InputSystem&) = delete;
    InputSystem& operator=(const InputSystem&) = delete;

    void ProcessWndMessage(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

    bool IsKeyPressed(KeyboardInput key);
    bool IsMouseButtonPressed(MouseInput button);

    std::optional<RawDelta> ReadRawDelta() noexcept;

protected:

    static const unsigned int KEYS_COUNT = 256u;
    static const unsigned int MOUSE_BUTTONS_COUNT = 256u;
    static const unsigned int RAW_DELTA_BUFFER_LIMIT = 16u;
    
    std::bitset<KEYS_COUNT> keyStates;
    std::bitset<MOUSE_BUTTONS_COUNT> mouseStates;

    std::queue<RawDelta> rawDeltaBuffer;

    void setKeyState(InputState state, KeyboardInput key);
    void setMouseButtonState(InputState state, MouseInput button);

    void onRawDelta(int dx, int dy);
    void trimRawInputBuffer();

    void clearState();

};

