#pragma once

#include "common.hpp"
#include "gl_object.hpp"

namespace frd::glfw {

    class Shader : public GlObject {
        public:
            enum class Type {
                Fragment = 0x8B30,
                Vertex   = 0x8B31,
            };

            std::string_view source;

            Shader(Type type, const std::string_view &source);
            ALWAYS_INLINE ~Shader() {
                this->Delete();
            }

            ALWAYS_INLINE void Delete() {
                glDeleteShader(this->handle);
            }

            bool Compile() const;
            std::string InfoLog() const;
    };

}