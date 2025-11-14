#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Vertex.h"

class Shader;
class Mesh;
class Shader;
class Texture;
class Transformation;
class LightManager;
class LightSource;
class Player;

// Classe Cube : represente un cube 3D dans le jeu
class Cube
{
public:
    // Constructeur
    // center : position du centre du cube
    // edge : taille d'une arête du cube
    // shader : shader utilisé pour le rendu
    // texture : texture appliquée au cube
    
    Cube(glm::vec3 center, float edge, Shader* shader, LightSource* lightSource, Player* player);
    Cube(glm::vec3 center, float edge, Shader* shader, Texture* texture, LightManager* lightManager, Player* player);
    Cube(glm::vec3 center, float edge, Shader* shader, Texture* texture, LightManager* lightManager, Player* player, Texture* specularMap);

    // Destructeur : libere la memoire (mesh, transformation…)
    ~Cube();

    // Mise à jour du cube (transformations, animations, effets…)
    void update();

    // Dessine le cube a l'ecran (appelle Mesh + Shader)
    virtual void draw();

	inline Transformation* getTransformation() const { return m_transformation; }

    // Retourne la texture du cube
    inline Texture* getTexture() const;

	inline glm::vec3 getCenter() const { return m_center; }

protected:
    Cube(glm::vec3 center, float edge, Shader* shader, Player* player);

    Mesh* m_mesh;                     // Maillage du cube (buffers OpenGL)
    Texture* m_texture;               // Texture appliquee
    Texture* m_specularMap;           // Texture speculaire
    Shader* m_shader;                 // Shader pour le rendu
    Transformation* m_transformation; // Transformations : position, rotation, scale
	LightManager* m_lightManager;     // Pointeur vers le LightBlock associé (si applicable)
	LightSource* m_lightSource;     // Pointeur vers le LightSource associé (si applicable)
    Player* m_player;

    std::vector<Vertex> m_vertices;       // Liste des sommets du cube
    std::vector<unsigned int> m_indices;  // Indices pour dessiner les triangles
    glm::vec3 m_center;                   // Centre du cube dans l'espace

    float m_edge;                         // Taille d'une arête du cube

private:
    void drawCubeShader();
    void drawLightSourceShader();
    void drawFlashlightShader();
    void drawSeverallight();
};