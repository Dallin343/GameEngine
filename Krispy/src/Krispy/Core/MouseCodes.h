//
// Created by dallin on 8/17/20.
//

#pragma once

namespace Krispy {
    typedef enum class MouseCode : uint16_t {
        MouseButton1 = 0,
        MouseButton2 = 1,
        MouseButton3 = 2,
        MouseButton4 = 3,
        MouseButton5 = 4,
        MouseButton6 = 5,
        MouseButton7 = 6,
        MouseButton8 = 7,

        MouseButtonLast = MouseButton8,
        MouseButtonLeft = MouseButton1,
        MouseButtonRight = MouseButton2,
        MouseButtonMiddle = MouseButton3
    } Mouse;

    inline std::ostream& operator<<(std::ostream& os, MouseCode button) {
        os << static_cast<int32_t>(button);
        return os;
    }
}

#define KRISPY_MOUSE_BUTTON_1         ::Krispy::Mouse::MouseButton1
#define KRISPY_MOUSE_BUTTON_2         ::Krispy::Mouse::MouseButton2
#define KRISPY_MOUSE_BUTTON_3         ::Krispy::Mouse::MouseButton3
#define KRISPY_MOUSE_BUTTON_4         ::Krispy::Mouse::MouseButton4
#define KRISPY_MOUSE_BUTTON_5         ::Krispy::Mouse::MouseButton5
#define KRISPY_MOUSE_BUTTON_6         ::Krispy::Mouse::MouseButton6
#define KRISPY_MOUSE_BUTTON_7         ::Krispy::Mouse::MouseButton7
#define KRISPY_MOUSE_BUTTON_8         ::Krispy::Mouse::MouseButton8
#define KRISPY_MOUSE_BUTTON_LAST      ::Krispy::Mouse::MouseButtonLast
#define KRISPY_MOUSE_BUTTON_LEFT      ::Krispy::Mouse::MouseButtonLeft
#define KRISPY_MOUSE_BUTTON_RIGHT     ::Krispy::Mouse::MouseButtonRight
#define KRISPY_MOUSE_BUTTON_MIDDLE    ::Krispy::Mouse::MouseButtonMiddle