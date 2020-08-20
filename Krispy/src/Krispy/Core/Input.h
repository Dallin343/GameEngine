//
// Created by dallin on 8/17/20.
//

#pragma once
#include "Krispy/Core/KeyCodes.h"
#include "Krispy/Core/MouseCodes.h"

namespace Krispy {
    class Input {
    public:
        static bool IsKeyPressed(KeyCode keycode);
        static bool IsMouseButtonPressed(MouseCode mousecode);

        static std::pair<float, float> GetMousePosition();

        static float GetMouseX();
        static float GetMouseY();
    };
}