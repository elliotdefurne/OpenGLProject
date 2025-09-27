#pragma once
#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <unordered_map>

#include "constants.h"

class Texture; // D�claration anticip�e pour �viter les include circulaires

// Structure repr�sentant un noeud de l'arborescence des textures
struct TextureNode {
    std::unordered_map<std::string, TextureNode*> children; // sous-dossiers
    Texture* texture = nullptr; // pointeur vers la texture si c'est une feuille
};

/**
 * @class TextureManager
 * @brief Charge et g�re toutes les textures d'un dossier pour OpenGL
 *
 * Cette classe fait 3 choses principales :
 * 1. Parcourt un dossier donn� et charge automatiquement toutes les images .png en tant que textures OpenGL.
 * 2. Organise les textures dans une arborescence (comme un explorateur de fichiers).
 * 3. Permet d'acc�der � une texture facilement via son chemin relatif.
 *
 * Notes importantes :
 * - Les textures sont stock�es en pointeurs bruts (Texture*). Le destructeur supprime
 *   ces pointeurs pour �viter les fuites m�moire.
 * - L'utilisation de std::filesystem (C++17) facilite le parcours des dossiers.
 */
class TextureManager {

public:
    /**
     * @brief Constructeur
     *
     * Charge automatiquement toutes les textures du dossier par d�faut (Constants::TEXTURES_FOLDER_PATH)
     */
    TextureManager();

    /**
     * @brief Destructeur
     *
     * Lib�re toutes les textures et tous les noeuds de l'arborescence.
     */
    ~TextureManager();

    /**
     * @brief R�cup�re une texture via son chemin relatif
     * @param path Chemin relatif (ex: "herbe.png" ou "dossier/sousdossier/texture.png")
     * @return Texture* Pointeur vers la texture
     * @throws std::out_of_range si le chemin est invalide ou la texture n'existe pas
     *
     * Exemple :
     * @code
     * Texture* tex = textureManager.getTexture("herbe.png");
     * glBindTexture(GL_TEXTURE_2D, tex->getID());
     * @endcode
     */
    Texture* getTexture(const std::string& path);

private:
    TextureNode m_root; ///< Racine de l'arborescence des textures

    /**
     * @brief Charge toutes les textures depuis un dossier donn�
     * @param texturesFolderPath Chemin du dossier (par d�faut : Constants::TEXTURES_FOLDER_PATH)
     *
     * �tapes du chargement :
     * 1. V�rifie que le dossier existe
     * 2. Parcourt tous les fichiers r�cursivement
     * 3. Pour chaque fichier .png, cr�e un objet Texture et l'ajoute � l'arborescence
     */
    void loadTextures(std::string texturesFolderPath = Constants::TEXTURES_FOLDER_PATH);

    /**
     * @brief Supprime r�cursivement tous les noeuds et textures de l'arborescence
     * @param node Pointeur vers le noeud � supprimer
     */
    void deleteNode(TextureNode* node);
};
