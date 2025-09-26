#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>

class Texture {
public:
    // Constructeur : charge la texture depuis un fichier et lui assigne un ID OpenGL
    Texture(const std::string& filePath, const int textureID);

    // Destructeur : libère la texture côté GPU
    ~Texture();

    // Accesseurs pour les propriétés de la texture
    inline int getWidth() const { return m_width; }      // Largeur en pixels
    inline int getHeight() const { return m_height; }    // Hauteur en pixels
    inline int getBPP() const { return m_BPP; }         // Bits par pixel
    inline GLuint getID() const { return m_textureID; } // ID OpenGL

private:
    // Charge la texture depuis le fichier et l'envoie sur le GPU
    void loadTexture();

    const std::string& m_filePath; // Chemin du fichier source de la texture
    GLuint m_textureID;             // ID OpenGL de la texture

    int m_width, m_height;          // Dimensions de la texture
    int m_nrChannels;               // Nombre de canaux (ex : 3 pour RGB, 4 pour RGBA)
    int m_BPP;                      // Bits par pixel
};
