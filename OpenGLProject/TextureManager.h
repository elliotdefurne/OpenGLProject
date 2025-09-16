#pragma once
#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>
#include <filesystem>

#include "Texture.h"
#include "constants.h"

struct TextureNode {
    std::unordered_map<std::string, TextureNode*> children; // sous-dossiers
    Texture* texture = nullptr; // si c'est une feuille avec une texture
};

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
        deleteNode(&m_root);
    };

    /**
     * @brief Retourne un pointeur vers une texture par son path.
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
    Texture* getTexture(const std::string& path) {
        std::stringstream ss(path);
        std::string part;
        TextureNode* current = &m_root;

        char sep = static_cast<char>(Constants::PREFERED_SEPARATOR_PATH);
        while (std::getline(ss, part, sep)) {
            auto it = current->children.find(part);
            if (it == current->children.end()) {
                throw std::out_of_range("Path not found: " + path);
            }
            current = it->second;
        }

        if (!current->texture) {
            throw std::out_of_range("No texture at path: " + path);
        }
        return current->texture;
    }

private:
    /// Noeuds qui contient toutes les textures chargées (pointeurs bruts).
    TextureNode m_root;

    /**
     * @brief Charge toutes les textures présentes dans un dossier.
     *
     * @param texturesFolderPath Chemin vers le dossier (par défaut : Constants::TEXTURES_FOLDER_PATH).
     *
     * Étapes du chargement :
     * 1. Vérifie que le dossier existe avec `std::filesystem::is_directory()`.
     * 2. Parcourt tous les fichiers recursivement avec `std::filesystem::recursive_directory_iterator`.
     * 3. Pour chaque fichier se terminant par ".png", crée une Texture et l’ajoute au unordered_map.
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
        for (const auto& entry : std::filesystem::recursive_directory_iterator(texturesFolderPath)) {
            if (entry.is_regular_file() && entry.path().extension() == ".png") {
                std::string relative = entry.path().lexically_relative(texturesFolderPath).string();

                // Découpe le chemin relatif en morceaux
                std::stringstream ss(relative);
                std::string part;
                TextureNode* current = &m_root;

                char sep = static_cast<char>(std::filesystem::path::preferred_separator);
                int id = 0;
                while (std::getline(ss, part, sep)) {
                    // Si c’est le dernier segment ET que c’est un fichier .png
                    if (ss.peek() == EOF) {
                        current->children[part] = new TextureNode();
                        current->children[part]->texture = new Texture(entry.path().string(), id);
                        id++;
                    }
                    else {
                        if (current->children.find(part) == current->children.end()) {
                            current->children[part] = new TextureNode();
                        }
                        current = current->children[part];
                    }
                }
            }
        }
    }
    void deleteNode(TextureNode* node) {
        for (auto& pair : node->children) {
            deleteNode(pair.second);
            delete pair.second;
        }
        if (node->texture) {
            delete node->texture;
        }
    }
};
