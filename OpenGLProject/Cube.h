#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Vertex.h"   // Structure d'un sommet (position, couleur, texture…)
#include "Mesh.h"     // Classe pour gerer les buffers OpenGL et dessiner
#include "Shader.h"   // Classe pour les shaders OpenGL
#include "Texture.h"  // Classe pour les textures
#include "Transformation.h" // Classe pour position, rotation et scale

// Classe Cube : represente un cube 3D dans le jeu
class Cube
{
public:
    // Constructeur
    // center : position du centre du cube
    // edge : taille d'une arête du cube
    // shader : shader utilisé pour le rendu
    // texture : texture appliquée au cube
    Cube(glm::vec3 center, float edge, Shader* shader, Texture* texture);

    // Destructeur : libere la memoire (mesh, transformation…)
    ~Cube();

    // Mise à jour du cube (transformations, animations, effets…)
    void update();

    // Dessine le cube a l'ecran (appelle Mesh + Shader)
    void draw();

    // Retourne la texture du cube
    inline Texture* getTexture() const { return m_mesh->getTexture(); }

private:
    Mesh* m_mesh;                     // Maillage du cube (buffers OpenGL)
    Texture* m_texture;               // Texture appliquée
    Shader* m_shader;                 // Shader pour le rendu
    Transformation* m_transformation; // Transformations : position, rotation, scale

    std::vector<Vertex> m_vertices;       // Liste des sommets du cube
    std::vector<unsigned int> m_indices;  // Indices pour dessiner les triangles
    glm::vec3 m_center;                   // Centre du cube dans l'espace

    float m_edge;                         // Taille d'une arête du cube
};
