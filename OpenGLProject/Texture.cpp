#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Texture.h"

/**
 * @class Texture
 * @brief Gère le chargement et l'utilisation d'une texture 2D dans OpenGL.
 *
 * Cette classe permet de charger une image (png, jpg, etc.) avec stb_image,
 * de l'envoyer dans la mémoire GPU et de configurer ses paramètres pour le rendu.
 */

 /**
  * @brief Constructeur de Texture.
  *
  * Charge immédiatement la texture en mémoire GPU.
  *
  * @param filePath Chemin vers le fichier image.
  * @param textureID Identifiant OpenGL de la texture.
  */
Texture::Texture(const std::string& filePath, const int textureID)
    : m_filePath(filePath), m_textureID(textureID) {
    loadTexture();
}

/**
 * @brief Destructeur de Texture.
 *
 * Supprime la texture côté GPU pour éviter les fuites de mémoire.
 */
Texture::~Texture() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &m_textureID);
}

/**
 * @brief Charge la texture depuis un fichier image.
 *
 * Étapes :
 * 1. Génère et bind la texture avec glGenTextures/glBindTexture.
 * 2. Configure les paramètres de wrapping et de filtrage.
 * 3. Inverse verticalement l'image pour OpenGL.
 * 4. Vérifie l'existence du fichier.
 * 5. Charge les pixels avec stbi_load.
 * 6. Copie les pixels dans le GPU via glTexImage2D.
 * 7. Génère les mipmaps.
 * 8. Libère la mémoire CPU.
 */
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
