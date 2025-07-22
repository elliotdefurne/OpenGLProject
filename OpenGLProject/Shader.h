#pragma once
#include <string>
#include <glad/glad.h> // Ou <GL/glew.h> si tu n'utilises pas glad

class Shader {
public:
    Shader(const std::string& vertexSource, const std::string& fragmentSource, bool isFile = false);
    ~Shader();

    void use() const;
    GLuint getID() const;

private:
    GLuint m_id;

    std::string loadFromFile(const std::string& path);
    GLuint compile(GLenum type, const std::string& source);
    void checkCompileErrors(GLuint shader, std::string type);
};
