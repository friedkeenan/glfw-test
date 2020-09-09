#pragma once

#include "common.hpp"

namespace frd::glfw {

    struct Vertex {
        float x, y, z;

        constexpr ALWAYS_INLINE Vertex(float x, float y, float z = 0) : x(x), y(y), z(z) { }
    };

}