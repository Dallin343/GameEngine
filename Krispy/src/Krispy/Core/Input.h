//
// Created by dallin on 8/17/20.
//

#pragma once

namespace Krispy {
    class Input {
    public:
        virtual bool IsKeyPressed(int keycode) = 0;
        virtual bool IsMouseButtonPressed(int mousecode) = 0;
    };
}