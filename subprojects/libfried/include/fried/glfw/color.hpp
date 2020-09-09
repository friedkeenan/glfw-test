#pragma once

#include "common.hpp"

namespace frd::glfw {

    class Color {
        public:
            std::uint8_t red, green, blue, alpha;

            constexpr Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 0xFF) : red(r), green(g), blue(b), alpha(a) { }
            constexpr Color(std::uint32_t rgb, std::uint8_t alpha = 0xFF) : Color((rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF, alpha) { }
            constexpr Color() : Color(0, 0, 0) { }

            constexpr ALWAYS_INLINE float RedFloat() const {
                return this->red / 255.0f;
            }

            constexpr ALWAYS_INLINE float GreenFloat() const {
                return this->green / 255.0f;
            }

            constexpr ALWAYS_INLINE float BlueFloat() const {
                return this->blue / 255.0f;
            }

            constexpr ALWAYS_INLINE float AlphaFloat() const {
                return this->alpha / 255.0f;
            }

            constexpr ALWAYS_INLINE bool operator ==(const Color &rhs) const {
                return this->red == rhs.red && this->green == rhs.green && this->blue == rhs.blue && this->alpha == rhs.alpha;
            }

            constexpr ALWAYS_INLINE bool operator !=(const Color &rhs) const {
                return this->red != rhs.red || this->green != rhs.green || this->blue != rhs.blue || this->alpha != rhs.alpha;
            }
    };

    static_assert(Color(0xAABBCC) == Color(0xAA, 0xBB, 0xCC));
    static_assert(Color(0xFF0000).RedFloat() == 1.0f);
    static_assert(Color(51, 0, 0).RedFloat() == 0.2f);

}