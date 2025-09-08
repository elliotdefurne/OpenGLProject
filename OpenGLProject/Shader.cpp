#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource, bool isFile) {
    std::string vertexCode = isFile ? loadFromFile(vertexSource) : vertexSource;
    std::string fragmentCode = isFile ? loadFromFile(fragmentSource) : fragmentSource;

    GLuint vertex = compile(GL_VERTEX_SHADER, vertexCode);
    GLuint fragment = compile(GL_FRAGMENT_SHADER, fragmentCode);

    m_id = glCreateProgram();
    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);
    glLinkProgram(m_id);

    checkCompileErrors(m_id, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    if (m_id) {
        glDeleteProgram(m_id);
    }
}

void Shader::use() const {
    glUseProgram(m_id);
}

GLuint Shader::getID() const {
    return m_id;
}

std::string Shader::loadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open shader file: " + path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void Shader::setTexture(const std::string& name, GLuint textureID, GLuint unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), unit);
}


GLuint Shader::compile(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    checkCompileErrors(shader, (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"));

    return shader;
}

void Shader::checkCompileErrors(GLuint object, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if (type == "PROGRAM") {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, 1024, nullptr, infoLog);
            throw std::runtime_error("Shader linking error:\n" + std::string(infoLog));
        }
    }
    else {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, 1024, nullptr, infoLog);
            throw std::runtime_error("Shader compilation error (" + type + "):\n" + std::string(infoLog));
        }
    }
}
