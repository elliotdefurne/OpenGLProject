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
 * @brief Classe utilitaire pour charger et gérer un ensemble de textures.
 *
 * Cette classe sert à :
 * - Parcourir un dossier et charger automatiquement toutes les images .png en tant que textures OpenGL.
 * - Stocker ces textures dans un vecteur de pointeurs.
 * - Fournir un accès simple à une texture par son index.
 *
 * Notes pour débutants :
 * - Les textures sont stockées en pointeurs bruts (Texture*). Le destructeur s’occupe
 *   de les libérer avec `delete`, ce qui évite les fuites mémoire.
 * - Si on demande une texture avec un index invalide, une exception `std::out_of_range` est lancée.
 * - L’utilisation de `std::filesystem` (C++17) permet de parcourir les dossiers facilement.
 */
class TextureManager {

public:
    /**
     * @brief Constructeur de TextureManager.
     *
     * Appelle automatiquement `loadTextures()` pour remplir la liste des textures.
     * Par défaut, le dossier défini dans `Constants::TEXTURES_FOLDER_PATH` est utilisé.
     */
    TextureManager() { loadTextures(); };

    /**
     * @brief Destructeur de TextureManager.
     *
     * Parcourt le vecteur et supprime chaque Texture*.
     * Cela permet de libérer correctement la mémoire CPU et GPU.
     */
    ~TextureManager() {
        for (auto& texture : m_textures) {
            delete texture;
        }
    };

    /**
     * @brief Retourne un pointeur vers une texture par son index.
     *
     * @param index Position dans le vecteur (0 = première texture).
     * @return Texture* Pointeur vers la texture demandée.
     *
     * @throws std::out_of_range si l’index est invalide.
     *
     * Exemple d’utilisation :
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
    /// Vecteur qui contient toutes les textures chargées (pointeurs bruts).
    std::vector<Texture*> m_textures;

    /**
     * @brief Charge toutes les textures présentes dans un dossier.
     *
     * @param texturesFolderPath Chemin vers le dossier (par défaut : Constants::TEXTURES_FOLDER_PATH).
     *
     * Étapes du chargement :
     * 1. Vérifie que le dossier existe avec `std::filesystem::is_directory()`.
     * 2. Parcourt tous les fichiers avec `std::filesystem::directory_iterator`.
     * 3. Pour chaque fichier se terminant par ".png", crée une Texture et l’ajoute au vecteur.
     *
     * Exemple :
     * - Si le dossier contient "herbe.png" et "pierre.png",
     *   le manager les chargera automatiquement et leur attribuera un ID.
     */
    void loadTextures(std::string texturesFolderPath = Constants::TEXTURES_FOLDER_PATH) {
        bool folderExists = std::filesystem::is_directory(texturesFolderPath);
        if (!folderExists) {
            std::cerr << "Le dossier des textures n’existe pas: " << texturesFolderPath << std::endl;
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
