#pragma once

#include "common.hpp"
#include "window.hpp"

namespace frd::glfw {

    namespace glad {

        ALWAYS_INLINE bool init() {
            return gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == 1;
        }

    }

    enum class InitHint : int {

    };

    class ApiWrapper {
        public:
            ALWAYS_INLINE Error InitHint(InitHint hint, int value) const {
                GLFW_TRY(glfwInitHint(static_cast<int>(hint), value));

                return ErrorSuccess;
            }

            ALWAYS_INLINE Error Init() const {
                GLFW_TRY(glfwInit());

                return ErrorSuccess;
            }

            ALWAYS_INLINE Error Terminate() const {
                GLFW_TRY(glfwTerminate());

                return ErrorSuccess;
            }

            ALWAYS_INLINE Error MakeContextCurrent(const Window &window) const {
                GLFW_TRY(glfwMakeContextCurrent(window.window));

                return ErrorSuccess;
            }

            ALWAYS_INLINE Error PollEvents() const {
                GLFW_TRY(glfwPollEvents());

                return ErrorSuccess;
            }
    };

}