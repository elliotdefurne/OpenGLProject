#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

/**
 * @brief Constructeur de Shader.
 *
 * Compile et lie les shaders à partir de sources ou de fichiers.
 *
 * @param vertexSource Code source ou chemin vers le shader de sommet.
 * @param fragmentSource Code source ou chemin vers le shader de fragment.
 * @param isFile Si true, les paramètres sont considérés comme des chemins de fichiers, sinon comme du code source direct.
 *
 * @throws std::runtime_error en cas d’échec de compilation ou de liaison des shaders.
 */
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

/**
 * @brief Destructeur de Shader.
 *
 * Libère le programme OpenGL associé si valide.
 */
Shader::~Shader() {
    if (m_id) {
        glDeleteProgram(m_id);
    }
}

/**
 * @brief Active le shader dans le contexte OpenGL courant.
 */
void Shader::use() const {
    glUseProgram(m_id);
}

/**
 * @brief Récupère l’identifiant OpenGL du programme.
 *
 * @return GLuint ID du programme.
 */
GLuint Shader::getID() const {
    return m_id;
}

/**
 * @brief Charge le contenu d’un fichier texte (shader GLSL).
 *
 * @param path Chemin vers le fichier.
 * @return std::string Contenu du fichier.
 *
 * @throws std::runtime_error si le fichier ne peut pas être ouvert.
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
 * @brief Lie une texture à une unité de texture et associe son uniform au shader.
 *
 * @param name Nom de l’uniform dans le shader.
 * @param textureID Identifiant OpenGL de la texture.
 * @param unit Indice de l’unité de texture (GL_TEXTURE0 + unit).
 */
void Shader::setTexture(const std::string& name, GLuint textureID, GLuint unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), unit);
}

/**
 * @brief Définit une matrice de transformation dans le shader.
 *
 * @param name Nom de l’uniform dans le shader.
 * @param trans Pointeur vers un objet Transformation contenant la matrice.
 */
void Shader::setTransformation(const std::string& name, Transformation* trans) const {
    unsigned int transformLoc = glGetUniformLocation(m_id, name.c_str());
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans->getMatrix()));
}

/**
 * @brief Compile un shader OpenGL à partir de son code source.
 *
 * @param type Type du shader (GL_VERTEX_SHADER ou GL_FRAGMENT_SHADER).
 * @param source Code GLSL à compiler.
 * @return GLuint Identifiant du shader compilé.
 *
 * @throws std::runtime_error si la compilation échoue.
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
 * @brief Vérifie et affiche les erreurs de compilation ou de linkage.
 *
 * @param object Identifiant du shader ou du programme.
 * @param type Type ("VERTEX", "FRAGMENT", ou "PROGRAM").
 *
 * @throws std::runtime_error avec le log d’erreur si compilation/liaison échoue.
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
