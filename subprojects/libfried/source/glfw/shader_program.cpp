namespace frd::glfw {

    bool ShaderProgram::Link() const {
        glLinkProgram(this->handle);

        int success;
        glGetProgramiv(this->handle, GL_LINK_STATUS, &success);

        return success == 0;
    }

    std::string ShaderProgram::InfoLog() const {
        std::string info(0x200, 0);
        glGetProgramInfoLog(this->handle, info.size(), nullptr, info.data());

        return info;
    }

}