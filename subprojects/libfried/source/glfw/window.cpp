namespace frd::glfw {

    namespace {

        /* 
            A bunch of shims and stuff for handling the callbacks.
            I'm sorry, I couldn't figure out a better way to handle
            callbacks while still preserving the OOP-style callbacks
        */
        std::unordered_map<GLFWwindow *, Window *> windows;

        void SizeCallbackShim(GLFWwindow *w, int width, int height) {
            auto window = windows[w];
            window->SizeCallback(width, height);
        }

    }

    Window::Window(int width, int height, const std::string &name, const GlVersion &version, const std::initializer_list<std::pair<WindowHint, int>> &hints) {
        this->SetVersion(version);

        for (auto [hint, value] : hints) {
            this->Hint(hint, value);
        }

        this->window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
        if (!this->IsValid()) {
            return;
        }

        windows[this->window] = this;

        glfwSetWindowSizeCallback(this->window, SizeCallbackShim);
    }

    Window::~Window() {
        glfwDestroyWindow(this->window);

        windows.erase(this->window);
    }

    Error Window::SetVersion(const GlVersion &version) const {
        E_TRY(this->Hint(WindowHint::VersionMajor, version.major));
        E_TRY(this->Hint(WindowHint::VersionMinor, version.minor));
        E_TRY(this->Hint(WindowHint::OpenGlProfile, version.profile));

        return ErrorSuccess;
    }

    void Window::SetBackground(const Color &color) const {
        glClearColor(color.RedFloat(), color.GreenFloat(), color.BlueFloat(), color.AlphaFloat());
        glClear(GL_COLOR_BUFFER_BIT);
    }

}