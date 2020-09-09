#pragma once

class MainWindow : public frd::glfw::Window {
    public:
        MainWindow(int width, int height, const std::string &name) : frd::glfw::Window(width, height, name) { }

        void SizeCallback(int width, int height) override {
            this->SetViewport(width, height);
        }
};