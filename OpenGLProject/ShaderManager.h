#pragma once
#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <unordered_map>

#include "Shader.h"
#include "Camera.h"
#include "constants.h"

struct ShaderNode {
    std::unordered_map<std::string, ShaderNode*> children;
    Shader* m_shader = nullptr;
};

class ShaderManager {
public:
    ShaderManager(Camera* camera) : m_camera(camera) { loadShaders(); };
    ~ShaderManager() {
        deleteNode(&m_root);
    };
    Shader* getShader(const std::string& path) {
        std::stringstream ss(path);
        std::string part;
        ShaderNode* current = &m_root;

        char sep = static_cast<char>(Constants::PREFERED_SEPARATOR_PATH);
        while (std::getline(ss, part, sep)) {
            auto it = current->children.find(part);
            if (it == current->children.end()) {
                throw std::out_of_range("Path not found: " + path);
            }
            current = it->second;
        }

        if (!current->m_shader) {
            throw std::out_of_range("No texture at path: " + path);
        }
        return current->m_shader;
    }
private:
    ShaderNode m_root;
    Camera* m_camera;
    void loadShaders(std::string shadersFolderPath = Constants::SHADERS_FOLDER_PATH) {
        if (!std::filesystem::is_directory(shadersFolderPath)) {
            std::cerr << "Le dossier des shaders n’existe pas: " << shadersFolderPath << std::endl;
            return;
        }
        for (const auto& entry : std::filesystem::recursive_directory_iterator(shadersFolderPath)) {
            if (entry.is_directory()) {
                // Vérifie si basic.vert et basic.frag existent dans ce dossier
                auto vertPath = entry.path() / "basic.vert";
                auto fragPath = entry.path() / "basic.frag";

                if (std::filesystem::exists(vertPath) && std::filesystem::exists(fragPath)) {
                    // Construit la hiérarchie de ShaderNode
                    std::string relative = entry.path().lexically_relative(shadersFolderPath).string();
                    std::stringstream ss(relative);
                    std::string part;
                    ShaderNode* current = &m_root;
                    char sep = static_cast<char>(std::filesystem::path::preferred_separator);

                    while (std::getline(ss, part, sep)) {
                        if (ss.peek() == EOF) {
                            // Dernier segment : associer un Shader
                            if (current->children.find(part) == current->children.end()) {
                                current->children[part] = new ShaderNode();
                            }
                            current->children[part]->m_shader = new Shader(
                                vertPath.string(),
                                fragPath.string(),
                                m_camera,
                                true
                            );
                        }
                        else {
                            // Crée les noeuds intermédiaires
                            if (current->children.find(part) == current->children.end()) {
                                current->children[part] = new ShaderNode();
                            }
                            current = current->children[part];
                        }
                    }
                }
            }
        }
    }
    void deleteNode(ShaderNode* node) {
        for (auto& pair : node->children) {
            deleteNode(pair.second);
            delete pair.second;
        }
        if (node->m_shader) {
            delete node->m_shader;
        }
    };
};
