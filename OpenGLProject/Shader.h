#pragma once
#include <string>
#include <glad/glad.h>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Transformation.h"
#include "Camera.h"

// Classe qui encapsule un shader OpenGL (vertex + fragment)
// Gère la compilation, le linkage, l'utilisation et l'envoi des variables uniformes
class Shader {
public:
    // Constructeur : compile et lie les shaders
    // vertexSource et fragmentSource peuvent être des chemins de fichiers ou du code source directement
    Shader(const std::string& vertexSource, const std::string& fragmentSource, Camera* camera, bool isFile);

    // Destructeur : supprime le programme shader côté GPU
    ~Shader();

    // Active ce shader pour le rendu et envoie les matrices model, view, projection
    void use();

    // Associe une texture 2D à un uniform du shader
    void setTexture(const std::string& name, GLuint textureID, GLuint unit = 0);

    // Envoie une transformation encapsulée dans la classe Transformation
    void setTransformation(const std::string& name, Transformation* trans);

    // Vide le cache des uniforms
    void clearUniformLocations();

    // Retourne l'identifiant OpenGL du programme shader
    GLuint getID() const;

    // Méthodes pour envoyer des variables uniformes simples
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

    // Méthodes pour modifier les matrices internes du shader
    void setModel(const glm::mat4& model) { m_model = model; }
    void setView(const glm::mat4& view) { m_view = view; }
    void setProjection(const glm::mat4& projection) { m_projection = projection; }

    // Méthodes pour obtenir les matrices internes
    const glm::mat4& getModel() const { return m_model; }
    const glm::mat4& getView() const { return m_view; }
    const glm::mat4& getProjection() const { return m_projection; }

private:
    GLuint m_id;  // ID OpenGL du programme shader
    Camera* m_camera;  // Pointeur vers la caméra pour récupérer la vue
    glm::mat4 m_projection, m_model, m_view = glm::mat4(1.0f);  // Matrices de transformation
    std::unordered_map<std::string, GLint> m_uniformLocations; // Cache des emplacements des uniforms

    // Charge le code source depuis un fichier
    std::string loadFromFile(const std::string& path);

    // Compile un shader GLSL (vertex ou fragment)
    GLuint compile(GLenum type, const std::string& source);

    // Vérifie les erreurs de compilation ou de linkage
    void checkCompileErrors(GLuint shader, std::string type);

    // Récupère l'emplacement d'un uniform dans le shader (avec cache)
    GLint getUniformLocation(const std::string& name);
};
