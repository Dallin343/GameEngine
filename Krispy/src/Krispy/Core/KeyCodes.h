//
// Created by dallin on 8/17/20.
//

#pragma once

#include <cstdint>

namespace Krispy {
    typedef enum class KeyCode : uint16_t {
        Space = 32,
        Apostrophe = 39,  /* ' */
        Comma = 44,  /* , */
        Minus = 45,  /* - */
        Period = 46,  /* . */
        Slash = 47,  /* / */

        D0 = 48,
        D1 = 49,
        D2 = 50,
        D3 = 51,
        D4 = 52,
        D5 = 53,
        D6 = 54,
        D7 = 55,
        D8 = 56,
        D9 = 57,

        Semicolon = 59,  /* ; */
        Equal = 61,  /* = */

        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,

        LeftBracket = 91,  /* [ */
        Backslash = 92,  /* \ */
        RightBracket = 93,  /* ] */
        GraveAccent = 96,  /* ` */
        World1 = 161, /* non-US #1 */
        World2 = 162, /* non-US #2 */

        /* Function keys */
        Escape = 256,
        Enter = 257,
        Tab = 258,
        Backspace = 259,
        Insert = 260,
        Delete = 261,
        Right = 262,
        Left = 263,
        Down = 264,
        Up = 265,
        PageUp = 266,
        PageDown = 267,
        Home = 268,
        End = 269,
        CapsLock = 280,
        ScrollLock = 281,
        NumLock = 282,
        PrintScreen = 283,
        Pause = 284,

        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,
        F13 = 302,
        F14 = 303,
        F15 = 304,
        F16 = 305,
        F17 = 306,
        F18 = 307,
        F19 = 308,
        F20 = 309,
        F21 = 310,
        F22 = 311,
        F23 = 312,
        F24 = 313,
        F25 = 314,

        KP0 = 320,
        KP1 = 321,
        KP2 = 322,
        KP3 = 323,
        KP4 = 324,
        KP5 = 325,
        KP6 = 326,
        KP7 = 327,
        KP8 = 328,
        KP9 = 329,
        KPDecimal = 330,
        KPDivide = 331,
        KPMultiply = 332,
        KPSubtract = 333,
        KPAdd = 334,
        KPEnter = 335,
        KPEqual = 336,
        LeftShift = 340,
        LeftControl = 341,
        LeftAlt = 342,
        LeftMeta = 343,
        RightShift = 344,
        RightControl = 345,
        RightAlt = 346,
        RightMeta = 347,
        Menu = 348
    } Key;

    inline std::ostream& operator<<(std::ostream& os, KeyCode keycode) {
        os << static_cast<int32_t>(keycode);
        return os;
    }
}

/* Printable keys */
#define KRISPY_KEY_SPACE              ::Krispy::Key::Space
#define KRISPY_KEY_APOSTROPHE         ::Krispy::Key::Apostrophe          /* ' */
#define KRISPY_KEY_COMMA              ::Krispy::Key::Comma               /* , */
#define KRISPY_KEY_MINUS              ::Krispy::Key::Minus               /* - */
#define KRISPY_KEY_PERIOD             ::Krispy::Key::Period              /* . */
#define KRISPY_KEY_SLASH              ::Krispy::Key::Slash               /* / */
#define KRISPY_KEY_0                  ::Krispy::Key::D0
#define KRISPY_KEY_1                  ::Krispy::Key::D1
#define KRISPY_KEY_2                  ::Krispy::Key::D2
#define KRISPY_KEY_3                  ::Krispy::Key::D3
#define KRISPY_KEY_4                  ::Krispy::Key::D4
#define KRISPY_KEY_5                  ::Krispy::Key::D5
#define KRISPY_KEY_6                  ::Krispy::Key::D6
#define KRISPY_KEY_7                  ::Krispy::Key::D7
#define KRISPY_KEY_8                  ::Krispy::Key::D8
#define KRISPY_KEY_9                  ::Krispy::Key::D9
#define KRISPY_KEY_SEMICOLON          ::Krispy::Key::Semicolon           /* ; */
#define KRISPY_KEY_EQUAL              ::Krispy::Key::Equal               /* = */
#define KRISPY_KEY_A                  ::Krispy::Key::A
#define KRISPY_KEY_B                  ::Krispy::Key::B
#define KRISPY_KEY_C                  ::Krispy::Key::C
#define KRISPY_KEY_D                  ::Krispy::Key::D
#define KRISPY_KEY_E                  ::Krispy::Key::E
#define KRISPY_KEY_F                  ::Krispy::Key::F
#define KRISPY_KEY_G                  ::Krispy::Key::G
#define KRISPY_KEY_H                  ::Krispy::Key::H
#define KRISPY_KEY_I                  ::Krispy::Key::I
#define KRISPY_KEY_J                  ::Krispy::Key::J
#define KRISPY_KEY_K                  ::Krispy::Key::K
#define KRISPY_KEY_L                  ::Krispy::Key::L
#define KRISPY_KEY_M                  ::Krispy::Key::M
#define KRISPY_KEY_N                  ::Krispy::Key::N
#define KRISPY_KEY_O                  ::Krispy::Key::O
#define KRISPY_KEY_P                  ::Krispy::Key::P
#define KRISPY_KEY_Q                  ::Krispy::Key::Q
#define KRISPY_KEY_R                  ::Krispy::Key::R
#define KRISPY_KEY_S                  ::Krispy::Key::S
#define KRISPY_KEY_T                  ::Krispy::Key::T
#define KRISPY_KEY_U                  ::Krispy::Key::U
#define KRISPY_KEY_V                  ::Krispy::Key::V
#define KRISPY_KEY_W                  ::Krispy::Key::W
#define KRISPY_KEY_X                  ::Krispy::Key::X
#define KRISPY_KEY_Y                  ::Krispy::Key::Y
#define KRISPY_KEY_Z                  ::Krispy::Key::Z
#define KRISPY_KEY_LEFT_BRACKET       ::Krispy::Key::LeftBracket        /* [ */
#define KRISPY_KEY_BACKSLASH          ::Krispy::Key::Backslash           /* \ */
#define KRISPY_KEY_RIGHT_BRACKET      ::Krispy::Key::RightBracket       /* ] */
#define KRISPY_KEY_GRAVE_ACCENT       ::Krispy::Key::GraveAccent        /* ` */
#define KRISPY_KEY_WORLD_1            ::Krispy::Key::World1            /* non-US #1 */
#define KRISPY_KEY_WORLD_2            ::Krispy::Key::World2            /* non-US #2 */

/* Function keys */
#define KRISPY_KEY_ESCAPE             ::Krispy::Key::Escape
#define KRISPY_KEY_ENTER              ::Krispy::Key::Enter
#define KRISPY_KEY_TAB                ::Krispy::Key::Tab
#define KRISPY_KEY_BACKSPACE          ::Krispy::Key::Backspace
#define KRISPY_KEY_INSERT             ::Krispy::Key::Insert
#define KRISPY_KEY_DELETE             ::Krispy::Key::Delete
#define KRISPY_KEY_RIGHT              ::Krispy::Key::Right
#define KRISPY_KEY_LEFT               ::Krispy::Key::Left
#define KRISPY_KEY_DOWN               ::Krispy::Key::Down
#define KRISPY_KEY_UP                 ::Krispy::Key::Up
#define KRISPY_KEY_PAGE_UP            ::Krispy::Key::PageUp
#define KRISPY_KEY_PAGE_DOWN          ::Krispy::Key::PageDown
#define KRISPY_KEY_HOME               ::Krispy::Key::Home
#define KRISPY_KEY_END                ::Krispy::Key::End
#define KRISPY_KEY_CAPS_LOCK          ::Krispy::Key::CapsLock
#define KRISPY_KEY_SCROLL_LOCK        ::Krispy::Key::ScrollLock
#define KRISPY_KEY_NUM_LOCK           ::Krispy::Key::NumLock
#define KRISPY_KEY_PRINT_SCREEN       ::Krispy::Key::PrintScreen
#define KRISPY_KEY_PAUSE              ::Krispy::Key::Pause
#define KRISPY_KEY_F1                 ::Krispy::Key::F1
#define KRISPY_KEY_F2                 ::Krispy::Key::F2
#define KRISPY_KEY_F3                 ::Krispy::Key::F3
#define KRISPY_KEY_F4                 ::Krispy::Key::F4
#define KRISPY_KEY_F5                 ::Krispy::Key::F5
#define KRISPY_KEY_F6                 ::Krispy::Key::F6
#define KRISPY_KEY_F7                 ::Krispy::Key::F7
#define KRISPY_KEY_F8                 ::Krispy::Key::F8
#define KRISPY_KEY_F9                 ::Krispy::Key::F9
#define KRISPY_KEY_F10                ::Krispy::Key::F10
#define KRISPY_KEY_F11                ::Krispy::Key::F11
#define KRISPY_KEY_F12                ::Krispy::Key::F12
#define KRISPY_KEY_F13                ::Krispy::Key::F13
#define KRISPY_KEY_F14                ::Krispy::Key::F14
#define KRISPY_KEY_F15                ::Krispy::Key::F15
#define KRISPY_KEY_F16                ::Krispy::Key::F16
#define KRISPY_KEY_F17                ::Krispy::Key::F17
#define KRISPY_KEY_F18                ::Krispy::Key::F18
#define KRISPY_KEY_F19                ::Krispy::Key::F19
#define KRISPY_KEY_F20                ::Krispy::Key::F20
#define KRISPY_KEY_F21                ::Krispy::Key::F21
#define KRISPY_KEY_F22                ::Krispy::Key::F22
#define KRISPY_KEY_F23                ::Krispy::Key::F23
#define KRISPY_KEY_F24                ::Krispy::Key::F24
#define KRISPY_KEY_F25                ::Krispy::Key::F25
#define KRISPY_KEY_KP_0               ::Krispy::Key::KP0
#define KRISPY_KEY_KP_1               ::Krispy::Key::KP1
#define KRISPY_KEY_KP_2               ::Krispy::Key::KP2
#define KRISPY_KEY_KP_3               ::Krispy::Key::KP3
#define KRISPY_KEY_KP_4               ::Krispy::Key::KP4
#define KRISPY_KEY_KP_5               ::Krispy::Key::KP5
#define KRISPY_KEY_KP_6               ::Krispy::Key::KP6
#define KRISPY_KEY_KP_7               ::Krispy::Key::KP7
#define KRISPY_KEY_KP_8               ::Krispy::Key::KP8
#define KRISPY_KEY_KP_9               ::Krispy::Key::KP9
#define KRISPY_KEY_KP_DECIMAL         ::Krispy::Key::KPDecimal
#define KRISPY_KEY_KP_DIVIDE          ::Krispy::Key::KPDivide
#define KRISPY_KEY_KP_MULTIPLY        ::Krispy::Key::KPMultiply
#define KRISPY_KEY_KP_SUBTRACT        ::Krispy::Key::KPSubtract
#define KRISPY_KEY_KP_ADD             ::Krispy::Key::KPAdd
#define KRISPY_KEY_KP_ENTER           ::Krispy::Key::KPEnter
#define KRISPY_KEY_KP_EQUAL           ::Krispy::Key::KPEqual
#define KRISPY_KEY_LEFT_SHIFT         ::Krispy::Key::LeftShift
#define KRISPY_KEY_LEFT_CONTROL       ::Krispy::Key::LeftControl
#define KRISPY_KEY_LEFT_ALT           ::Krispy::Key::LeftAlt
#define KRISPY_KEY_LEFT_SUPER         ::Krispy::Key::LeftMeta
#define KRISPY_KEY_RIGHT_SHIFT        ::Krispy::Key::Rightshift
#define KRISPY_KEY_RIGHT_CONTROL      ::Krispy::Key::RightControl
#define KRISPY_KEY_RIGHT_ALT          ::Krispy::Key::RightAlt
#define KRISPY_KEY_RIGHT_SUPER        ::Krispy::Key::RightMeta
#define KRISPY_KEY_MENU               ::Krispy::Key::Menu


/*! @defgroup mods Modifier key flags
 *  @brief Modifier key flags.
 *
 *  See [key input](@ref input_key) for how these are used.
 *
 *  @ingroup input
 *  @{ */

/*! @brief If this bit is set one or more Shift keys were held down.
 *
 *  If this bit is set one or more Shift keys were held down.
 */
#define KRISPY_MOD_SHIFT           0x0001
/*! @brief If this bit is set one or more Control keys were held down.
 *
 *  If this bit is set one or more Control keys were held down.
 */
#define KRISPY_MOD_CONTROL         0x0002
/*! @brief If this bit is set one or more Alt keys were held down.
 *
 *  If this bit is set one or more Alt keys were held down.
 */
#define KRISPY_MOD_ALT             0x0004
/*! @brief If this bit is set one or more Super keys were held down.
 *
 *  If this bit is set one or more Super keys were held down.
 */
#define KRISPY_MOD_SUPER           0x0008
/*! @brief If this bit is set the Caps Lock key is enabled.
 *
 *  If this bit is set the Caps Lock key is enabled and the @ref
 *  KRISPY_LOCK_KEY_MODS input mode is set.
 */
#define KRISPY_MOD_CAPS_LOCK       0x0010
/*! @brief If this bit is set the Num Lock key is enabled.
 *
 *  If this bit is set the Num Lock key is enabled and the @ref
 *  KRISPY_LOCK_KEY_MODS input mode is set.
 */
#define KRISPY_MOD_NUM_LOCK        0x0020