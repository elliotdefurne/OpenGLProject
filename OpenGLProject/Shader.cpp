#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "Shader.h"
#include "Constants.h"
#include "Camera.h"

/**
 * @class Shader
 * @brief Classe pour gérer les shaders OpenGL (vertex + fragment)
 *
 * Gère :
 * - Compilation et linkage des shaders
 * - Envoi des variables uniformes (matrices, textures)
 * - Activation du shader pour le rendu
 */

 /**
  * @brief Constructeur : compile et lie les shaders
  *
  * @param vertexSource Chemin ou code source du vertex shader
  * @param fragmentSource Chemin ou code source du fragment shader
  * @param camera Pointeur vers la caméra pour récupérer la vue
  * @param isFile Indique si vertexSource et fragmentSource sont des chemins de fichiers
  */
Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource, Camera* camera, bool isFile) {
    m_model = glm::mat4(1.0f);
    m_view = glm::mat4(1.0f);
    m_projection = glm::mat4(1.0f);
    m_camera = camera;

    m_view = m_camera->getViewMatrix();

    // Projection en perspective : effet 3D avec champ de vision de 60°
    m_projection = glm::perspective(
        glm::radians(60.0f),
        (float)Constants::WINDOW_WIDTH / (float)Constants::WINDOW_HEIGHT,
        0.1f, 100.0f
    );

    // Chargement du code source
    std::string vertexCode = isFile ? loadFromFile(vertexSource) : vertexSource;
    std::string fragmentCode = isFile ? loadFromFile(fragmentSource) : fragmentSource;

    // Compilation individuelle
    GLuint vertex = compile(GL_VERTEX_SHADER, vertexCode);
    GLuint fragment = compile(GL_FRAGMENT_SHADER, fragmentCode);

    // Création et linkage du programme
    m_id = glCreateProgram();
    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);
    glLinkProgram(m_id);

    checkCompileErrors(m_id, "PROGRAM");

    // Shaders bruts supprimés après linkage
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

/**
 * @brief Destructeur : supprime le programme shader côté GPU
 */
Shader::~Shader() {
    if (m_id) {
        glDeleteProgram(m_id);
    }
}

/**
 * @brief Active ce shader et envoie les matrices au GPU
 */
void Shader::use() {
    m_view = m_camera->getViewMatrix();

    glUseProgram(m_id);

    setMat4("model", m_model);
    setMat4("view", m_view);
    setMat4("projection", m_projection);
}

/**
 * @brief Retourne l'identifiant OpenGL du shader
 */
GLuint Shader::getID() const {
    return m_id;
}

/**
 * @brief Charge un shader depuis un fichier texte
 * @param path Chemin du fichier
 * @return Contenu du fichier
 * @throws runtime_error si le fichier ne peut pas être ouvert
 */
std::string Shader::loadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open shader file: " + path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

/**
 * @brief Associe une texture 2D à un uniform du shader
 * @param name Nom de l'uniform
 * @param textureID ID OpenGL de la texture
 * @param unit Unité de texture (slot)
 */
void Shader::setTexture(const std::string& name, GLuint textureID, GLuint unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniform1i(getUniformLocation(name), unit);
}

/**
 * @brief Envoie une transformation au shader
 * @param name Nom de l'uniform
 * @param trans Pointeur vers une Transformation contenant une matrice
 */
void Shader::setTransformation(const std::string& name, Transformation* trans) {
    unsigned int transformLoc = getUniformLocation(name);
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans->getMatrix()));
}

/**
 * @brief Compile un shader GLSL
 * @param type Type (GL_VERTEX_SHADER ou GL_FRAGMENT_SHADER)
 * @param source Code source GLSL
 * @return ID du shader compilé
 */
GLuint Shader::compile(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    checkCompileErrors(shader, (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"));

    return shader;
}

/**
 * @brief Vérifie les erreurs de compilation ou de linkage
 * @param object ID du shader ou du programme
 * @param type "VERTEX", "FRAGMENT" ou "PROGRAM"
 * @throws runtime_error si erreur détectée
 */
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

/**
 * @brief Récupère l'emplacement d'un uniform dans le shader
 * @param name Nom de l'uniform
 * @return Position de l'uniform dans le programme
 * @throws invalid_argument si l'uniform n'existe pas
 */
GLint Shader::getUniformLocation(const std::string& name) {
    auto it = m_uniformLocations.find(name);
    if (it == m_uniformLocations.end()) {
        GLint location = glGetUniformLocation(m_id, name.c_str());
        if (location == -1) {
            throw std::invalid_argument("Uniform " + name + " not found.");
        }
        m_uniformLocations[name] = location;
        return location;
    }
    return it->second;  // Retourne la valeur mise en cache
}

/**
 * @brief Vide le cache des uniforms
 */
void Shader::clearUniformLocations() {
    m_uniformLocations.clear();
}
