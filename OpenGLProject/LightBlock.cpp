#include "LightBlock.h"

#include "Vertex.h"   // Structure d'un sommet (position, couleur, texture…)
#include "Mesh.h"     // Classe pour gerer les buffers OpenGL et dessiner
#include "Shader.h"   // Classe pour les shaders OpenGL
#include "Texture.h"  // Classe pour les textures
#include "Transformation.h" // Classe pour position, rotation et scale

LightBlock::LightBlock(glm::vec3 center, float edge, Shader* shader, Texture* texture) : Cube(center, edge, shader, texture) {

}

LightBlock::~LightBlock() {

}

void LightBlock::draw() {
    m_shader->clearUniformLocations();                          // Nettoie les anciens réglages du shader
    m_shader->setModel(m_transformation->getMatrix());          // Envoie la matrice "modèle" (position/rotation/scale)
    m_shader->use();                                            // Active le shader
    m_shader->setTexture("ourTexture", m_texture->getID());     // Associe la texture au shader
    m_mesh->draw();                                             // Demande à OpenGL de dessiner le maillage
}
