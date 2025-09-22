#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "Shader.h"
#include "Constants.h"
#include "Camera.h"

/**
 * @class Shader
 * @brief Classe qui encapsule la gestion des shaders OpenGL (vertex + fragment).
 *
 * Un shader est un petit programme exécuté directement sur la carte graphique.
 * Il existe plusieurs types de shaders, mais les deux principaux sont :
 * - Le **vertex shader** : il s'occupe de transformer les sommets (positions, normales, etc.).
 * - Le **fragment shader** : il détermine la couleur finale des pixels.
 *
 * Cette classe gère :
 * - La compilation et le linkage des shaders.
 * - L'envoi de variables (uniforms) au GPU (matrices, textures...).
 * - L'utilisation du programme shader dans la pipeline OpenGL.
 */
Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource, Camera* camera, bool isFile) {
    m_model = glm::mat4(1.0f);
    m_view = glm::mat4(1.0f);
    m_projection = glm::mat4(1.0f);
    m_camera = camera;

	m_view = m_camera->getViewMatrix();

    // Projection en perspective : effet "3D" avec un champ de vision de 60°
    m_projection = glm::perspective(
        glm::radians(60.0f),
        (float)Constants::WINDOW_WIDTH / (float)Constants::WINDOW_HEIGHT,
        0.1f,   // Plan de coupe proche
        100.0f  // Plan de coupe lointain
    );

    // Chargement du code source : depuis fichier ou directement depuis une string
    std::string vertexCode = isFile ? loadFromFile(vertexSource) : vertexSource;
    std::string fragmentCode = isFile ? loadFromFile(fragmentSource) : fragmentSource;

    // Compilation individuelle des shaders
    GLuint vertex = compile(GL_VERTEX_SHADER, vertexCode);
    GLuint fragment = compile(GL_FRAGMENT_SHADER, fragmentCode);

    // Création et linkage du programme shader
    m_id = glCreateProgram();
    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);
    glLinkProgram(m_id);

    checkCompileErrors(m_id, "PROGRAM");

    // Les shaders bruts ne sont plus nécessaires une fois linkés au programme
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

/**
 * @brief Destructeur qui libère la mémoire GPU associée au programme shader.
 *
 * En C++, le destructeur est appelé automatiquement quand un objet sort de portée.
 * Ici, on supprime le programme côté OpenGL pour éviter des fuites mémoire GPU.
 */
Shader::~Shader() {
    if (m_id) {
        glDeleteProgram(m_id);
    }
}

/**
 * @brief Active l'utilisation du shader dans la pipeline graphique.
 *
 * Chaque fois qu’on dessine des objets, il faut indiquer à OpenGL
 * quel programme shader utiliser. Cette fonction active celui-ci.
 *
 * Elle envoie aussi automatiquement les matrices model, view et projection
 * au shader, pour gérer la transformation 3D -> 2D.
 */
void Shader::use() {
    glUseProgram(m_id);

    setMat4("model", m_model);
    setMat4("view", m_view);
    setMat4("projection", m_projection);
}

/**
 * @brief Retourne l'identifiant OpenGL du programme shader.
 * @return GLuint ID du programme.
 */
GLuint Shader::getID() const {
    return m_id;
}

/**
 * @brief Charge le code source d’un shader depuis un fichier texte.
 * @param path Chemin du fichier.
 * @return Contenu du fichier sous forme de string.
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
 * @brief Associe une texture 2D à une variable uniforme du shader.
 *
 * @param name Nom de l'uniform dans le shader (par ex. "diffuseMap").
 * @param textureID Identifiant OpenGL de la texture.
 * @param unit Unité de texture (GL_TEXTURE0, GL_TEXTURE1, etc.).
 *
 * Explication : dans OpenGL, une texture est liée à une "unit" (slot).
 * On dit ensuite au shader que la variable correspond à ce slot.
 */
void Shader::setTexture(const std::string& name, GLuint textureID, GLuint unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniform1i(getUniformLocation(name), unit);
}

/**
 * @brief Envoie une matrice de transformation personnalisée au shader.
 *
 * @param name Nom de l'uniform dans le shader.
 * @param trans Pointeur vers une Transformation contenant une matrice 4x4.
 *
 * Ici, `Transformation` est une classe externe qui encapsule des opérations
 * comme translation, rotation et mise à l’échelle.
 */
void Shader::setTransformation(const std::string& name, Transformation* trans) {
    unsigned int transformLoc = getUniformLocation(name);
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans->getMatrix()));
}

/**
 * @brief Compile un shader (vertex ou fragment).
 *
 * @param type Type de shader (GL_VERTEX_SHADER ou GL_FRAGMENT_SHADER).
 * @param source Code source du shader GLSL.
 * @return GLuint ID du shader compilé.
 *
 * Étapes :
 * 1. Créer un objet shader avec glCreateShader.
 * 2. Associer le code source avec glShaderSource.
 * 3. Compiler le shader avec glCompileShader.
 * 4. Vérifier les erreurs de compilation.
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
 * @param object ID du shader ou du programme.
 * @param type Type ("VERTEX", "FRAGMENT", ou "PROGRAM").
 * @throws std::runtime_error si une erreur est détectée.
 *
 * OpenGL ne plante pas tout seul : il faut demander explicitement
 * les logs d'erreur et lever une exception côté C++ si nécessaire.
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
 * @brief Récupère l’emplacement d’une variable uniforme dans le shader.
 *
 * @param name Nom de l'uniform dans le code GLSL.
 * @return GLint Position de la variable dans le programme.
 * @throws std::invalid_argument si l'uniform n'existe pas.
 *
 * Les "uniforms" sont des variables globales du shader (par ex. matrices, couleurs...).
 * Elles doivent être envoyées depuis le CPU au GPU avant le rendu.
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
    return it->second;  // Retourner la valeur trouvée dans le cache
}

void Shader::clearUniformLocations() {
    m_uniformLocations.clear();
}