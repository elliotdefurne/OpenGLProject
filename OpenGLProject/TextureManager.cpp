#include "TextureManager.h"
#include "Texture.h"

TextureManager::TextureManager() {
	loadTextures();
}

TextureManager::~TextureManager() {
    deleteNode(&m_root);
};

Texture* TextureManager::getTexture(const std::string& path) {
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

void TextureManager::loadTextures(std::string texturesFolderPath) {
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
                    current->children[part]->texture = new Texture(entry.path().string(), id, Materials::PLASTIC_GLOSSY);
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

void TextureManager::deleteNode(TextureNode* node) {
    for (auto& pair : node->children) {
        deleteNode(pair.second);
        delete pair.second;
    }
    if (node->texture) {
        delete node->texture;
    }
}