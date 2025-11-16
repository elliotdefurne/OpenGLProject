#pragma once
#include <string>
#include <iostream>
#include <filesystem>

class Shader;

// Classe Texture : représente une texture chargée sur le GPU OpenGL
class Texture {
public:
    /**
     * @brief Constructeur : charge la texture depuis un fichier
     * @param filePath Chemin du fichier image
     * @param textureID ID OpenGL à assigner à la texture
     */
    Texture(const std::string& filePath, const int textureID, float shininess);

    /**
     * @brief Destructeur : libère la texture côté GPU
     */
    ~Texture();

    // Accesseurs pour les propriétés de la texture
    inline int getWidth() const { return m_width; }          // Largeur en pixels
    inline int getHeight() const { return m_height; }        // Hauteur en pixels
    inline int getBPP() const { return m_BPP; }             // Bits par pixel
    inline unsigned int getID() const { return m_textureID; } // ID OpenGL
    void applyToShader(Shader* shader, Texture* specularMap);

private:
    /**
     * @brief Charge la texture depuis le fichier et l'envoie sur le GPU
     */
    void loadTexture();

    const std::string& m_filePath; // Chemin du fichier source de la texture
    unsigned int m_textureID;      // ID OpenGL de la texture

    int m_width, m_height;         // Dimensions de la texture
    int m_nrChannels;              // Nombre de canaux (ex: 3 pour RGB, 4 pour RGBA)
    int m_BPP;                     // Bits par pixel
    float m_shininess;
    bool m_isSpecular;
};
