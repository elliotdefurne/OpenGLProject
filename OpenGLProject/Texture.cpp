#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Texture.h"
#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Texture::Texture(const std::string& filePath, const int textureID, float shininess, bool hasSpecular)
    : m_filePath(filePath), m_textureID(textureID), m_shininess(shininess) {
	printf("Loading texture from: %s\n", filePath.c_str());
    m_hasSpecular = hasSpecular; // Si il trouve _specular.png dans le filename
    loadTexture(m_filePath, m_textureID);

	// Chargement de la texture spéculaire si applicable

    if (m_hasSpecular) {
		// Générer le chemin du fichier spéculaire

		m_fileSpecularPath = m_filePath;
        m_specularTextureID = textureID + 1;

        std::string ancien = ".png";
        std::string nouvelle = "_specular.png";

		// Remplacement de la partie du nom de fichier
        size_t pos = m_fileSpecularPath.find(ancien);
        if (pos != std::string::npos) { m_fileSpecularPath.replace(pos, ancien.length(), nouvelle); }

        loadTexture(m_fileSpecularPath, m_specularTextureID);
    }
}

Texture::~Texture() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &m_textureID);
	if (m_hasSpecular) glDeleteTextures(1, &m_specularTextureID);
}

void Texture::loadTexture(std::string& filePath, unsigned int& id) {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    // Paramètres de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Inverser l'image verticalement
    stbi_set_flip_vertically_on_load(true);

    // Vérifier si le fichier existe
    bool filepathExists = std::filesystem::exists(filePath);
    if (!filepathExists) {
        std::cerr << "File path does not exist: " << filePath << std::endl;
        return;
    }

    // Chargement de l'image en RGBA
    unsigned char* data = stbi_load(filePath.c_str(), &m_width, &m_height, &m_nrChannels, 4);
    if (data) {
        m_nrChannels = 4;
        GLenum format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cerr << "Failed to load texture: " << filePath << std::endl;
    }

    // Libération de la mémoire CPU
    stbi_image_free(data);
}


void Texture::applyToShader(Shader* shader) {
    shader->setTexture("material.diffuse", m_textureID, 0);

    if (m_hasSpecular) {
        shader->setTexture("material.specular", m_specularTextureID, 1);
    }
    else {
        shader->setTexture("material.specular", m_defaultSpecularID, 1);
    }

    shader->setFloat("material.shininess", m_shininess);
}