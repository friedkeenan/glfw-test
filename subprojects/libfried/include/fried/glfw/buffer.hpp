#pragma once

#include "common.hpp"
#include "gl_object.hpp"

namespace frd::glfw {

    enum class DrawType {
        Stream  = 0x88E0,
        Static  = 0x88E4,
        Dynamic = 0x88E8,
    };

    class Buffer : public GlObject {
        public:
            enum class Type {
                Array = 0x8892,
            };

            Type type;

            ALWAYS_INLINE Buffer(Type type) {
                glGenBuffers(1, &this->handle);
                this->type = type;
            }

            ALWAYS_INLINE void Bind() {
                glBindBuffer(static_cast<unsigned int>(this->type), this->handle);
            }
            
            ALWAYS_INLINE void SendData(const void *data, std::size_t size, DrawType draw = DrawType::Static) {
                glBufferData(static_cast<unsigned int>(this->type), size, data, static_cast<unsigned int>(draw));
            }
    };

    class VertexBuffer : public Buffer {
        public:
            ALWAYS_INLINE VertexBuffer() : Buffer(Buffer::Type::Array) { }
    };

}