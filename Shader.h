#pragma once
#include <string>
#include <glad/glad.h>
#include "Transformation.h"


class Shader {
public:
    Shader(const std::string& vertexSource, const std::string& fragmentSource, bool isFile = false);
    ~Shader();

    void use() const;
    void setTexture(const std::string& name, GLuint textureID, GLuint unit = 0) const;
    void setTransformation(const std::string& name, Transformation* trans) const;
    GLuint getID() const;

private:
    GLuint m_id;

    std::string loadFromFile(const std::string& path);
    GLuint compile(GLenum type, const std::string& source);
    void checkCompileErrors(GLuint shader, std::string type);
};
