#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Vertex.h"

class Shader;
class Mesh;
class Shader;
class Texture;
class Transformation;

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
    virtual void draw();

    // Retourne la texture du cube
    inline Texture* getTexture() const;

protected:
    Mesh* m_mesh;                     // Maillage du cube (buffers OpenGL)
    Texture* m_texture;               // Texture appliquée
    Shader* m_shader;                 // Shader pour le rendu
    Transformation* m_transformation; // Transformations : position, rotation, scale

    std::vector<Vertex> m_vertices;       // Liste des sommets du cube
    std::vector<unsigned int> m_indices;  // Indices pour dessiner les triangles
    glm::vec3 m_center;                   // Centre du cube dans l'espace

    float m_edge;                         // Taille d'une arête du cube
};
