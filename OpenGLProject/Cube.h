#pragma once
#include <glm/glm.hpp>
#include <vector>

#include "Vertex.h"
#include "Mesh.h"
#include "Shader.h"

class Cube
{
public:
    // Constructeur : crée un cube à partir de son centre, de la taille de son arête,
    // du shader utilisé et de sa texture
    Cube(glm::vec3 center, float edge, Shader* shader, Texture* texture);

    // Destructeur : libère la mémoire (mesh, etc.)
    ~Cube();

    // Mise à jour du cube (transformations, animations…)
    void update();

    // Dessine le cube (appel au Mesh + Shader)
    void draw();

    // Getter pour récupérer la texture du cube
    inline Texture* getTexture() const { return m_mesh->getTexture(); }

private:
    Mesh* m_mesh;                  // Maillage du cube (contient les buffers OpenGL)
    Texture* m_texture;            // Texture appliquée au cube
    Shader* m_shader;              // Shader utilisé pour le rendu
    Transformation* m_transformation; // Transformation du cube (position, rotation, scale)

    std::vector<Vertex> m_vertices;       // Liste des sommets du cube
    std::vector<unsigned int> m_indices;  // Indices (ordre pour dessiner les triangles)
    glm::vec3 m_center;                   // Centre du cube dans l’espace

    float m_edge;                         // Longueur d’une arête du cube
};

