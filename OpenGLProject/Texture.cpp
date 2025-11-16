#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Texture.h"
#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Texture::Texture(const std::string& filePath, const int textureID, float shininess)
    : m_filePath(filePath), m_textureID(textureID), m_shininess(shininess) {
    m_isSpecular = filePath.find("_specular") != std::string::npos; // Si il trouve _specular dans le chemin
    loadTexture();
    
}

Texture::~Texture() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &m_textureID);
}

void Texture::loadTexture() {
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    // Paramètres de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Inverser l'image verticalement
    stbi_set_flip_vertically_on_load(true);

    // Vérifier si le fichier existe
    bool filepathExists = std::filesystem::exists(m_filePath);
    if (!filepathExists) {
        std::cerr << "File path does not exist: " << m_filePath << std::endl;
        return;
    }

    // Chargement de l'image en RGBA
    unsigned char* data = stbi_load(m_filePath.c_str(), &m_width, &m_height, &m_nrChannels, 4);
    if (data) {
        m_nrChannels = 4;
        GLenum format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cerr << "Failed to load texture: " << m_filePath << std::endl;
    }

    // Libération de la mémoire CPU
    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, m_textureID);
}


void Texture::applyToShader(Shader* shader, Texture* specularMap) {
    shader->setTexture("material.diffuse", m_textureID, 0);
    if (specularMap) {
        shader->setTexture("material.specular", specularMap->getID(), 1);
    }
    else {
        shader->setTexture("material.specular", m_textureID, 1);
    }

    shader->setFloat("material.shininess", m_shininess);
}