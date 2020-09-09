#pragma once

#include "common.hpp"

namespace frd::glfw {

    class GlObject {
        public:
            unsigned int handle;

            constexpr ALWAYS_INLINE GlObject() = default;
            constexpr ALWAYS_INLINE GlObject(unsigned int handle) : handle(handle) { }

            virtual ~GlObject() = default;

            constexpr ALWAYS_INLINE bool IsValid() const {
                return this->handle != 0;
            }
    };

}