#include "pch.h"

#include "InputSystem.h"

#include <winuser.h>
#include <memory>
#include <iostream>

void InputSystem::ProcessWndMessage(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
    unsigned int keycode = wparam;

    switch (umessage)
    {
        case WM_KILLFOCUS:
            clearState();
            break;

        // Keyboard
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
            setKeyState(InputState::Pressed, static_cast<KeyboardInput>(keycode));
            break;
        case WM_SYSKEYUP:
        case WM_KEYUP:
            setKeyState(InputState::Released, static_cast<KeyboardInput>(keycode));
            break;

        // Mouse
        case WM_LBUTTONDOWN:
            setMouseButtonState(InputState::Pressed, MouseInput::Left);
            break;
        case WM_LBUTTONUP:
            setMouseButtonState(InputState::Released, MouseInput::Left);
            break;
        case WM_RBUTTONDOWN:
            setMouseButtonState(InputState::Pressed, MouseInput::Right);
            break;
        case WM_RBUTTONUP:
            setMouseButtonState(InputState::Released, MouseInput::Right);
            break;
        case WM_MBUTTONDOWN:
            setMouseButtonState(InputState::Pressed, MouseInput::Middle);
            break;
        case WM_MBUTTONUP:
            setMouseButtonState(InputState::Released, MouseInput::Middle);
            break;
        case WM_MOUSEMOVE:
            //onMouseMove(LOWORD(lparam), HIWORD(lparam));
            break;

        case WM_INPUT:
        {
            UINT dataSize;
            // Need to populate data size first
            GetRawInputData(reinterpret_cast<HRAWINPUT>(lparam),
                RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));

            if (dataSize > 0)
            {
                std::unique_ptr<BYTE[]> rawdata = std::make_unique<BYTE[]>(dataSize);
                if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lparam),
                    RID_INPUT, rawdata.get(), &dataSize, sizeof(RAWINPUTHEADER)) == dataSize)
                {
                    RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawdata.get());
                    if (raw->header.dwType == RIM_TYPEMOUSE)
                    {
                        onRawDelta(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
                    }
                }
            }
            break;
        }
    }
}

bool InputSystem::IsKeyPressed(const KeyboardInput key)
{
    return keyStates[static_cast<size_t>(key)] == 1;
}

bool InputSystem::IsMouseButtonPressed(const MouseInput button)
{
    return mouseStates[static_cast<size_t>(button)] == 1;
}

std::optional<InputSystem::RawDelta> InputSystem::ReadRawDelta() noexcept
{
    if (rawDeltaBuffer.empty())
    {
        return std::nullopt;
    }
    const RawDelta d = rawDeltaBuffer.front();
    rawDeltaBuffer.pop();
    return d;
}

void InputSystem::onRawDelta(const int dx, const int dy)
{
    rawDeltaBuffer.push({ dx, dy });
    trimRawInputBuffer();
}

void InputSystem::trimRawInputBuffer()
{
    while (rawDeltaBuffer.size() > RAW_DELTA_BUFFER_LIMIT)
    {
        rawDeltaBuffer.pop();
    }
}

void InputSystem::setKeyState(const InputState state, const KeyboardInput key)
{
    keyStates[static_cast<size_t>(key)] = static_cast<bool>(state);
}

void InputSystem::setMouseButtonState(const InputState state, const MouseInput button)
{
    mouseStates[static_cast<size_t>(button)] = static_cast<bool>(state);
}

void InputSystem::clearState()
{
    keyStates.reset();
    mouseStates.reset();
}
