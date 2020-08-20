//
// Created by dallin on 8/19/20.
//

#pragma once

namespace Krispy {
    class GraphicsContext {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };
}