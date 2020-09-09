#pragma once

#include "common.hpp"

namespace frd::glfw {

    /*
        An abstraction for GLFW errors.
        The description is only valid until the
        next error occurs or GLFW is terminated.
    */
    class Error {
        public:
            static constexpr char DefaultDescription[] = "No description";
            
            int error_code;
            std::string_view description;

            constexpr Error(int ec) : error_code(ec), description(DefaultDescription) { }

            constexpr Error(int ec, const std::string_view &desc) : error_code(ec), description(desc) { }

            constexpr ALWAYS_INLINE bool IsSuccess() const {
                return this->error_code == 0;
            }

            constexpr ALWAYS_INLINE bool IsFailure() const {
                return this->error_code != 0;
            }
    };

    constexpr auto ErrorSuccess = Error(0, "No error");

}

#define GLFW_ERROR(expr)                                    \
    ({                                                      \
        (expr);                                             \
        const char *_desc;                                  \
        const auto _ec = glfwGetError(&_desc);              \
        if (_desc == nullptr) {                             \
            _desc = ::frd::glfw::Error::DefaultDescription; \
        }                                                   \
        auto _error = ::frd::glfw::Error(_ec, _desc);       \
        _error;                                             \
    })

#define E_TRY(expr)                             \
    ({                                          \
        ::frd::glfw::Error _error = (expr);     \
        if (FRD_UNLIKELY(_error.IsFailure())) { \
            return _error;                      \
        }                                       \
    })

#define E_ASSERT(expr)                                                                                                               \
    ({                                                                                                                               \
        ::frd::glfw::Error _error = (expr);                                                                                          \
        if (FRD_UNLIKELY(_error.IsFailure())) {                                                                                      \
            std::fprintf(stderr, "%s:%d | %#x (%s)\n", __PRETTY_FUNCTION__, __LINE__, _error.error_code, _error.description.data()); \
            exit(-1);                                                                                                                \
        }                                                                                                                            \
    })

#define GLFW_TRY(expr) E_TRY(GLFW_ERROR(expr))

#define GLFW_ASSERT(expr) E_ASSERT(GLFW_ERROR(expr))