#pragma once

enum class InputState
{
    Pressed = 1,
    Released = 0
};

enum class InputType
{
    Keyboard,
    Mouse
};

enum class MouseInput
{
    Left = 0x01,
    Right = 0x02,
    Middle = 0x04
};

// KeyCodes
// https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
enum class KeyboardInput
{
    Escape = 0x1B,
    Backspace = 0x08,
    Tab = 0x09,
    Enter = 0x0D,
    Shift = 0x10,
    Ctrl = 0x11,
    Alt = 0x12,
    Pause = 0x13,
    CapsLock = 0x14,
    Scape = 0x20,

    Arrow_Left = 0x25,
    Arrow_Up = 0x26,
    Arrow_Right = 0x27,
    Arrow_Down = 0x28,

    Num_0 = 0x30,
    Num_1 = 0x31,
    Num_2 = 0x32,
    Num_3 = 0x33,
    Num_4 = 0x34,
    Num_5 = 0x35,
    Num_6 = 0x36,
    Num_7 = 0x37,
    Num_8 = 0x38,
    Num_9 = 0x39,

    Key_A = 0x41,
    Key_B = 0x42,
    Key_C = 0x43,
    Key_D = 0x44,
    Key_E = 0x45,
    Key_F = 0x46,
    Key_G = 0x47,
    Key_H = 0x48,
    Key_I = 0x49,
    Key_J = 0x4A,
    Key_K = 0x4B,
    Key_L = 0x4C,
    Key_M = 0x4D,
    Key_N = 0x4E,
    Key_O = 0x4F,
    Key_P = 0x50,
    Key_Q = 0x51,
    Key_R = 0x52,
    Key_S = 0x53,
    Key_T = 0x54,
    Key_U = 0x55,
    Key_V = 0x56,
    Key_W = 0x57,
    Key_X = 0x58,
    Key_Y = 0x59,
    Key_Z = 0x5A,

    Multiply = 0x6A,
    Add = 0x6B,
    Separator = 0x6C,
    Subtract = 0x6D,
    Decimal = 0x6E,
    Divide = 0x6F,

    F1 = 0x70,
    F2 = 0x71,
    F3 = 0x72,
    F4 = 0x73,
    F5 = 0x74,
    F6 = 0x75,
    F7 = 0x76,
    F8 = 0x77,
    F9 = 0x78,
    F10 = 0x79,
    F11 = 0x7A,
    F12 = 0x7B,
};