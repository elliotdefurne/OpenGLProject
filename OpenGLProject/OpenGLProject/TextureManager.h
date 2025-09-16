#pragma once
#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>
#include <filesystem>

#include "Texture.h"
#include "constants.h"

/**
 * @class TextureManager
 * @brief Classe utilitaire pour charger et g�rer un ensemble de textures.
 *
 * Cette classe sert � :
 * - Parcourir un dossier et charger automatiquement toutes les images .png en tant que textures OpenGL.
 * - Stocker ces textures dans un vecteur de pointeurs.
 * - Fournir un acc�s simple � une texture par son index.
 *
 * Notes pour d�butants :
 * - Les textures sont stock�es en pointeurs bruts (Texture*). Le destructeur s�occupe
 *   de les lib�rer avec `delete`, ce qui �vite les fuites m�moire.
 * - Si on demande une texture avec un index invalide, une exception `std::out_of_range` est lanc�e.
 * - L�utilisation de `std::filesystem` (C++17) permet de parcourir les dossiers facilement.
 */
class TextureManager {

public:
    /**
     * @brief Constructeur de TextureManager.
     *
     * Appelle automatiquement `loadTextures()` pour remplir la liste des textures.
     * Par d�faut, le dossier d�fini dans `Constants::TEXTURES_FOLDER_PATH` est utilis�.
     */
    TextureManager() { loadTextures(); };

    /**
     * @brief Destructeur de TextureManager.
     *
     * Parcourt le vecteur et supprime chaque Texture*.
     * Cela permet de lib�rer correctement la m�moire CPU et GPU.
     */
    ~TextureManager() {
        for (auto& texture : m_textures) {
            delete texture;
        }
    };

    /**
     * @brief Retourne un pointeur vers une texture par son index.
     *
     * @param index Position dans le vecteur (0 = premi�re texture).
     * @return Texture* Pointeur vers la texture demand�e.
     *
     * @throws std::out_of_range si l�index est invalide.
     *
     * Exemple d�utilisation :
     * @code
     * Texture* tex = textureManager.getTexture(0);
     * glBindTexture(GL_TEXTURE_2D, tex->getID());
     * @endcode
     */
    Texture* getTexture(const int index) {
        if (0 <= index && index < m_textures.size()) {
            return m_textures.at(index);
        }
        else {
            throw std::out_of_range("Texture index out of range");
        }
    }

private:
    /// Vecteur qui contient toutes les textures charg�es (pointeurs bruts).
    std::vector<Texture*> m_textures;

    /**
     * @brief Charge toutes les textures pr�sentes dans un dossier.
     *
     * @param texturesFolderPath Chemin vers le dossier (par d�faut : Constants::TEXTURES_FOLDER_PATH).
     *
     * �tapes du chargement :
     * 1. V�rifie que le dossier existe avec `std::filesystem::is_directory()`.
     * 2. Parcourt tous les fichiers avec `std::filesystem::directory_iterator`.
     * 3. Pour chaque fichier se terminant par ".png", cr�e une Texture et l�ajoute au vecteur.
     *
     * Exemple :
     * - Si le dossier contient "herbe.png" et "pierre.png",
     *   le manager les chargera automatiquement et leur attribuera un ID.
     */
    void loadTextures(std::string texturesFolderPath = Constants::TEXTURES_FOLDER_PATH) {
        bool folderExists = std::filesystem::is_directory(texturesFolderPath);
        if (!folderExists) {
            std::cerr << "Le dossier des textures n�existe pas: " << texturesFolderPath << std::endl;
            return;
        }
        for (const auto& entry : std::filesystem::directory_iterator(texturesFolderPath)) {
            const int stringLength = static_cast<int>(entry.path().string().size());
            if (entry.is_regular_file() && entry.path().string().substr(stringLength - 4) == ".png") {
                std::string filePath = entry.path().string();
                int textureID = static_cast<int>(m_textures.size());
                m_textures.emplace_back(new Texture(filePath, textureID));
            }
        }
    }
};
