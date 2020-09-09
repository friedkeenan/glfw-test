namespace frd::glfw {

    Shader::Shader(Shader::Type type, const std::string_view &source)
     : GlObject(glCreateShader(static_cast<unsigned int>(type))) {
        this->source = source;
    }

    bool Shader::Compile() const {
        auto src = this->source.data();
        auto size = static_cast<int>(this->source.size());
        glShaderSource(this->handle, 1, &src, &size);
        glCompileShader(this->handle);

        int success;
        glGetShaderiv(this->handle, GL_COMPILE_STATUS, &success);

        return success != 0;
    }

    std::string Shader::InfoLog() const {
        std::string info(0x200, 0);
        glGetShaderInfoLog(this->handle, info.size(), nullptr, info.data());

        return info;
    }

}