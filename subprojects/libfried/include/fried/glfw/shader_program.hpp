#pragma once

namespace frd::glfw {

    class ShaderProgram : public GlObject {
        public:
            template <typename ...Args>
            ALWAYS_INLINE ShaderProgram(Args &&... args) : GlObject(glCreateProgram()) {
                (glAttachShader(this->handle, args.handle), ...);
                (args.Delete(), ...);
            }

            bool Link() const;
            std::string InfoLog() const;

            ALWAYS_INLINE void Use(std::function<void()> f) {
                glUseProgram(this->handle);

                f();

                glUseProgram(0);
            }
    };

}