#pragma once

#include "common.hpp"

namespace frd::glfw {
    enum class WindowHint : int {
        VersionMajor  = 0x00022002,
        VersionMinor  = 0x00022003,
        OpenGlProfile = 0x00022007,
    };

    enum class Key : int {
        Space      = 32,
        Apostrophe = 39,
        Comma      = 44,
        Minus      = 45,
        Period     = 46,
        Slash      = 47,

        Zero  = 48,
        One   = 49,
        Two   = 50,
        Three = 51,
        Four  = 52,
        Five  = 53,
        Six   = 54,
        Seven = 55,
        Eight = 56,
        Nine  = 57,

        Semicolon = 59,
        Equal     = 61,

        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69, /* Nice */
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,

        LeftBracket  = 91,
        Backslash    = 92,
        RightBracket = 93,
        GraveAccent  = 96,

        WorldOne = 161,
        WorldTwo = 162,

        Escape      = 256,
        Enter       = 257,
        Tab         = 258,
        Backspace   = 259,
        Insert      = 260,
        Delete      = 261,
        Right       = 262,
        Left        = 263,
        Down        = 264,
        Up          = 265,
        PageUp      = 266,
        PageDown    = 267,
        Home        = 268,
        End         = 269,
        CapsLock    = 280,
        ScrollLock  = 281,
        NumLock     = 282,
        PrintScreen = 283,
        Pause       = 284,

        F1  = 290,
        F2  = 291,
        F3  = 292,
        F4  = 293,
        F5  = 294,
        F6  = 295,
        F7  = 296,
        F8  = 297,
        F9  = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,
        F13 = 302,
        F14 = 303,
        F15 = 304,
        F16 = 305,
        F17 = 306,
        F18 = 307,
        F19 = 308,
        F20 = 309,
        F21 = 310,
        F22 = 311,
        F23 = 312,
        F24 = 313,
        F25 = 314,

        KeypadZero  = 320,
        KeypadOne   = 321,
        KeypadTwo   = 322,
        KeypadThree = 323,
        KeypadFour  = 324,
        KeypadFive  = 325,
        KeypadSix   = 326,
        KeypadSeven = 327,
        KeypadEight = 328,
        KeypadNine  = 329,

        KeypadDecimal  = 330,
        KeypadDivide   = 331,
        KeypadMultiply = 332,
        KeypadSubtract = 333,
        KeypadAdd      = 334,
        KeypadEnter    = 335,
        KeypadEqual    = 336,

        LeftShift    = 340,
        LeftControl  = 341,
        LeftAlt      = 342,
        LeftSuper    = 343,
        RightShift   = 344,
        RightControl = 345,
        RightAlt     = 346,
        RightSuper   = 347,
        Menu         = 348,
    };

    struct GlVersion {
        int major;
        int minor;
        int profile;
    };

    class Window {
        public:
            GLFWwindow *window;

            Window(int width, int height, const std::string &name, const GlVersion &version = {3, 3, GLFW_OPENGL_CORE_PROFILE}, const std::initializer_list<std::pair<WindowHint, int>> &hints = {});
            Window(GLFWwindow *w) : window(w) { }

            virtual ~Window();

            ALWAYS_INLINE bool IsValid() const {
                return this->window != nullptr;
            }

            ALWAYS_INLINE Error Hint(WindowHint hint, int value) const {
                GLFW_TRY(glfwWindowHint(static_cast<int>(hint), value));

                return ErrorSuccess;
            }

            ALWAYS_INLINE Error Hint(WindowHint hint, const std::string &value) const {
                GLFW_TRY(glfwWindowHintString(static_cast<int>(hint), value.c_str()));

                return ErrorSuccess;
            }

            ALWAYS_INLINE void SetViewport(int width, int height, int x = 0, int y = 0) const {
                glViewport(x, y, width, height);
            }

            ALWAYS_INLINE std::pair<Error, bool> ShouldClose() const {
                bool should_close;
                Error error = GLFW_ERROR(should_close = glfwWindowShouldClose(this->window));

                return {error, should_close};
            }

            ALWAYS_INLINE Error SetShouldClose(bool should_close) const {
                GLFW_TRY(glfwSetWindowShouldClose(this->window, should_close));

                return ErrorSuccess;
            }

            ALWAYS_INLINE std::pair<Error, bool> IsKeyPressed(Key key) const {
                int state;
                Error error = GLFW_ERROR(state = glfwGetKey(this->window, static_cast<int>(key)));

                return {error, state == GLFW_PRESS};
            }

            ALWAYS_INLINE Error SwapBuffers() const {
                GLFW_TRY(glfwSwapBuffers(this->window));

                return ErrorSuccess;
            }

            Error SetVersion(const GlVersion &version) const;

            void SetBackground(const Color &color) const;

            virtual void SizeCallback(int width, int height) { }
    };
}