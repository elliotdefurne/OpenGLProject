#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Texture.h"

/**
 * @class Texture
 * @brief Gere le chargement et l'utilisation d'une texture 2D dans OpenGL.
 *
 * Une texture est une image appliquee sur une surface 3D (ex: cube, sol, personnage).
 * Cette classe utilise stb_image pour lire les fichiers image (png, jpg, etc.)
 * et cree une texture OpenGL.
 *
 * Etapes principales :
 * - Charger les pixels de l'image depuis le disque (RAM)
 * - Envoyer les pixels dans la memoire GPU (VRAM)
 * - Configurer les parametres de la texture (wrap, filtre)
 * - Generer les mipmaps (versions reduites de la texture pour le rendu a distance)
 */

 /**
  * @brief Constructeur de Texture.
  *
  * Prend le chemin du fichier image et un identifiant de texture,
  * puis charge immediatement la texture en memoire GPU.
  *
  * @param filePath Chemin vers le fichier image (ex: "res/texture.png").
  * @param textureID Identifiant unique de la texture (fourni par OpenGL).
  */
Texture::Texture(const std::string& filePath, const int textureID)
    : m_filePath(filePath), m_textureID(textureID) {
    loadTexture();
}

/**
 * @brief Destructeur de Texture.
 *
 * Libere automatiquement la memoire GPU utilisee par cette texture.
 * Appelle glDeleteTextures pour supprimer l'objet OpenGL associe.
 *
 * Important : OpenGL ne libere jamais la memoire automatiquement,
 * c'est au programmeur de le faire.
 */
Texture::~Texture() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &m_textureID);
}

/**
 * @brief Charge la texture depuis un fichier image.
 *
 * Etapes detaillees :
 * 1. Cree un nouvel objet texture avec glGenTextures().
 * 2. Configure ses parametres :
 *    - GL_TEXTURE_WRAP_S / T : mode d'enroulement (ici GL_REPEAT)
 *    - GL_TEXTURE_MIN_FILTER / MAG_FILTER : filtres de rendu
 * 3. Utilise stb_image pour charger les pixels de l'image (CPU).
 *    - stbi_load() retourne un pointeur vers les donnees brutes (RGBA).
 *    - stbi_set_flip_vertically_on_load(true) retourne l'image a l'endroit correct
 *      (car OpenGL et les fichiers image utilisent des origines differentes).
 * 4. Copie les pixels dans le GPU avec glTexImage2D().
 * 5. Genere automatiquement des mipmaps (textures reduites).
 *
 * Si le fichier n'existe pas ou que le chargement echoue,
 * un message d'erreur est affiche.
 */
void Texture::loadTexture() {
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    // Parametres de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Inverser l'image verticalement (necessaire pour OpenGL)
    stbi_set_flip_vertically_on_load(true);

    // Verifier si le chemin existe
    bool filepathExists = std::filesystem::exists(m_filePath);
    if (!filepathExists) {
        std::cerr << "File path does not exist: " << m_filePath << std::endl;
        return;
    }

    // Chargement de l'image (RGBA force, 4 canaux)
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

    // Liberer la memoire CPU (les pixels sont deja dans le GPU)
    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, m_textureID);
}
