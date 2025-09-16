#pragma once
#include <string>
#include <glad/glad.h>
#include <unordered_map>

#include "Transformation.h"



class Shader {
public:
    Shader(const std::string& vertexSource, const std::string& fragmentSource, bool isFile = false);
    ~Shader();

    void use();
    void setTexture(const std::string& name, GLuint textureID, GLuint unit = 0);
    void setTransformation(const std::string& name, Transformation* trans);
    void clearUniformLocations();
    GLuint getID() const;

    // Setters

    void setBool(const std::string& name, bool value) { glUniform1i(getUniformLocation(name), (int)value); }
    void setInt(const std::string& name, int value) { glUniform1i(getUniformLocation(name), value); }
    void setFloat(const std::string& name, float value) { glUniform1f(getUniformLocation(name), value); }
    void setVec2(const std::string& name, const glm::vec2& value) { glUniform2fv(getUniformLocation(name), 1, &value[0]); }
    void setVec2(const std::string& name, float x, float y) { glUniform2f(getUniformLocation(name), x, y); }
    void setVec3(const std::string& name, const glm::vec3& value) { glUniform3fv(getUniformLocation(name), 1, &value[0]); }
    void setVec3(const std::string& name, float x, float y, float z) { glUniform3f(getUniformLocation(name), x, y, z); }
    void setVec4(const std::string& name, const glm::vec4& value) { glUniform4fv(getUniformLocation(name), 1, &value[0]); }
    void setVec4(const std::string& name, float x, float y, float z, float w) { glUniform4f(getUniformLocation(name), x, y, z, w); }
    void setMat2(const std::string& name, const glm::mat2& mat) { glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]); }
    void setMat3(const std::string& name, const glm::mat3& mat) { glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]); }
    void setMat4(const std::string& name, const glm::mat4& mat) { glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]); }

    // Méthodes pour modifier les matrices
    void setModel(const glm::mat4& model) { m_model = model; }
    void setView(const glm::mat4& view) { m_view = view; }
    void setProjection(const glm::mat4& projection) { m_projection = projection; }

    // Méthodes pour obtenir les matrices
    const glm::mat4& getModel() const { return m_model; }
    const glm::mat4& getView() const { return m_view; }
    const glm::mat4& getProjection() const { return m_projection; }
private:
    GLuint m_id;
    glm::mat4 m_projection, m_model, m_view = glm::mat4(1.0f);
    std::unordered_map<std::string, GLint> m_uniformLocations;

    std::string loadFromFile(const std::string& path);
    GLuint compile(GLenum type, const std::string& source);
    void checkCompileErrors(GLuint shader, std::string type);
    GLint getUniformLocation(const std::string& name);
};
