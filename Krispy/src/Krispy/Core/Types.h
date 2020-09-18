//
// Created by dallin on 9/15/20.
//

#pragma once

namespace Krispy {
    enum class ShaderDataType {
        None = 0, Float, Float2, Float3, Float4,
        Int, Int2, Int3, Int4,
        Mat3, Mat4,
        Bool,
        Texture2D,
    };
}