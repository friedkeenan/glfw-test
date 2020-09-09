#include <random>

#include <shaders/triangle.vert>
#include <shaders/triangle.frag>

#include "main_window.hpp"

using frd::glfw::Key;
using frd::glfw::Color;

constexpr int WindowWidth = 800;
constexpr int WindowHeight = 600;

constexpr std::array vertices = {
    frd::glfw::Vertex(-0.5, -0.5),
    frd::glfw::Vertex(0.5, -0.5),
    frd::glfw::Vertex(0, 0.5),
};

int main(int argc, char **argv) {
    frd::glfw::ApiWrapper api;
    E_ASSERT(api.Init());
    ON_SCOPE_EXIT { api.Terminate(); };

    MainWindow window(WindowWidth, WindowHeight, "LearnOpenGL");
    B_ASSERT(window.IsValid());
    E_ASSERT(api.MakeContextCurrent(window));

    B_ASSERT(frd::glfw::glad::init());

    window.SetViewport(0, 0, WindowWidth, WindowHeight);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int8_t> dis(-4, 4);

    Color bg_color(0x800080);

    frd::glfw::Buffer vert_buf(frd::glfw::Buffer::Type::Array);
    vert_buf.Bind();
    vert_buf.SendData(vertices.data(), vertices.size());

    frd::glfw::Shader vert(frd::glfw::Shader::Type::Vertex, triangle_vert);
    std::printf("%u\n", vert.handle);
    std::printf("%d\n", vert.Compile());

    frd::glfw::Shader frag(frd::glfw::Shader::Type::Fragment, triangle_vert);
    std::printf("%u\n", frag.handle);
    std::printf("%d\n", frag.Compile());

    frd::glfw::ShaderProgram prog(vert, frag);
    std::printf("%d\n", prog.Link());

    while (true) {
        auto [error_close, should_close] = window.ShouldClose();
        if (should_close) 
            break;

        E_ASSERT(error_close);

        auto [error_pressed, pressed] = window.IsKeyPressed(Key::Space);
        E_ASSERT(error_pressed);

        if (pressed) {
            bg_color.red += dis(gen);
            bg_color.green += dis(gen);
            bg_color.blue += dis(gen);
        }

        window.SetBackground(bg_color);

        E_ASSERT(window.SwapBuffers());
        E_ASSERT(api.PollEvents());
    }

    return 0;
}