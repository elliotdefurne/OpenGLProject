#pragma once
#include <glm/glm.hpp>
#include <vector>

#include "Vertex.h"
#include "Mesh.h"
#include "Shader.h"

class Cube
{
public:
    // Constructeur : cr�e un cube � partir de son centre, de la taille de son ar�te,
    // du shader utilis� et de sa texture
    Cube(glm::vec3 center, float edge, Shader* shader, Texture* texture);

    // Destructeur : lib�re la m�moire (mesh, etc.)
    ~Cube();

    // Mise � jour du cube (transformations, animations�)
    void update();

    // Dessine le cube (appel au Mesh + Shader)
    void draw();

    // Getter pour r�cup�rer la texture du cube
    inline Texture* getTexture() const { return m_mesh->getTexture(); }

private:
    Mesh* m_mesh;                  // Maillage du cube (contient les buffers OpenGL)
    Texture* m_texture;            // Texture appliqu�e au cube
    Shader* m_shader;              // Shader utilis� pour le rendu
    Transformation* m_transformation; // Transformation du cube (position, rotation, scale)

    std::vector<Vertex> m_vertices;       // Liste des sommets du cube
    std::vector<unsigned int> m_indices;  // Indices (ordre pour dessiner les triangles)
    glm::vec3 m_center;                   // Centre du cube dans l�espace

    float m_edge;                         // Longueur d�une ar�te du cube
};

