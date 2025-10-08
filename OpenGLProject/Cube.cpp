#include "Cube.h"

#include "Vertex.h"   // Structure d'un sommet (position, couleur, texture…)
#include "Mesh.h"     // Classe pour gerer les buffers OpenGL et dessiner
#include "Shader.h"   // Classe pour les shaders OpenGL
#include "Texture.h"  // Classe pour les textures
#include "Transformation.h" // Classe pour position, rotation et scale
#include "LightSource.h"


// Constructeur du cube
Cube::Cube(glm::vec3 center, float edge, Shader* shader, Texture* texture, LightSource* light)
	: m_center(center), m_edge(edge), m_shader(shader), m_texture(texture), m_light(light), m_specularMap(nullptr) {
    // Coordonnées du centre du cube
    float x = center[0];
    float y = center[1];
    float z = center[2];

    // Moitié de la taille du cube (sert à placer les sommets autour du centre)
    float halfEdge = m_edge / 2.0f;

    // Création des composants nécessaires
    m_mesh = new Mesh();                     // Le "maillage" (contient les infos pour OpenGL)
    m_transformation = new Transformation(); // Permet de déplacer/faire tourner/agrandir l’objet

    // Définition des sommets du cube
    // Chaque face a 4 sommets, et comme un cube a 6 faces -> 24 sommets en tout
    // Chaque sommet a : position (x,y,z), normale (ici mise à 0 pour l’instant), coordonnées UV
    m_vertices = {
        // Face avant (Z+)
        Vertex(x - halfEdge, y - halfEdge, z + halfEdge, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
        Vertex(x + halfEdge, y - halfEdge, z + halfEdge, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
        Vertex(x + halfEdge, y + halfEdge, z + halfEdge, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),
        Vertex(x - halfEdge, y + halfEdge, z + halfEdge, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),

        // Face arrière (Z-)
        Vertex(x - halfEdge, y - halfEdge, z - halfEdge, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
        Vertex(x + halfEdge, y - halfEdge, z - halfEdge, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
        Vertex(x + halfEdge, y + halfEdge, z - halfEdge, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),
        Vertex(x - halfEdge, y + halfEdge, z - halfEdge, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),

        // Face gauche (X-)
        Vertex(x - halfEdge, y - halfEdge, z - halfEdge, -1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
        Vertex(x - halfEdge, y - halfEdge, z + halfEdge, -1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
        Vertex(x - halfEdge, y + halfEdge, z + halfEdge, -1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),
        Vertex(x - halfEdge, y + halfEdge, z - halfEdge, -1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),

        // Face droite (X+)
        Vertex(x + halfEdge, y - halfEdge, z - halfEdge, 1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
        Vertex(x + halfEdge, y - halfEdge, z + halfEdge, 1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
        Vertex(x + halfEdge, y + halfEdge, z + halfEdge, 1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),
        Vertex(x + halfEdge, y + halfEdge, z - halfEdge, 1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),

        // Face du bas (Y-)
        Vertex(x - halfEdge, y - halfEdge, z - halfEdge, 0.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
        Vertex(x + halfEdge, y - halfEdge, z - halfEdge, 0.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),
        Vertex(x + halfEdge, y - halfEdge, z + halfEdge, 0.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),
        Vertex(x - halfEdge, y - halfEdge, z + halfEdge, 0.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),

        // Face du haut (Y+)
        Vertex(x - halfEdge, y + halfEdge, z - halfEdge, 0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
        Vertex(x + halfEdge, y + halfEdge, z - halfEdge, 0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),
        Vertex(x + halfEdge, y + halfEdge, z + halfEdge, 0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),
        Vertex(x - halfEdge, y + halfEdge, z + halfEdge, 0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f)
    };

    // Indices : disent dans quel ordre relier les sommets pour former les triangles
    // Chaque face du cube = 2 triangles = 6 indices
    m_indices = {
        0, 1, 2,   2, 3, 0,     // Face avant (Z+)
        5, 4, 7,   7, 6, 5,     // Face arrière (Z-)
        8, 9, 10,  10, 11, 8,   // Face gauche (X-)
        13, 12, 15, 15, 14, 13, // Face droite (X+)
        17, 16, 19, 19, 18, 17, // Face du bas (Y-)
        20, 21, 22, 22, 23, 20  // Face du haut (Y+)
    };
    m_mesh->load(m_vertices, m_indices, m_texture);
}

Cube::Cube(glm::vec3 center, float edge, Shader* shader, Texture* texture, Texture* specularMap, LightSource* light): Cube(center, edge, shader, texture, light) {
    m_specularMap = specularMap;
}

// Destructeur -> appelé quand on détruit l’objet Cube
// Libère la mémoire utilisée
Cube::~Cube() {
    m_vertices.clear();       // Vide la liste de sommets
    m_indices.clear();        // Vide la liste d’indices
    delete m_mesh;            // Détruit le mesh
    delete m_transformation;  // Détruit la transformation
}

inline Texture* Cube::getTexture() const {
    return m_mesh->getTexture();
}

// Prépare le cube pour être affiché (envoie les données au GPU)
void Cube::update() {
   
}

// Dessine le cube à l’écran
void Cube::draw() {
    m_shader->clearUniformLocations();                          // Nettoie les anciens réglages du shader
    m_shader->setModel(m_transformation->getMatrix());          // Envoie la matrice "modèle" (position/rotation/scale)
    m_shader->use();                                            // Active le shader

    if (m_shader->getName() == "cube") {
        drawCubeShader();
    }
    else if (m_shader->getName() == "specularMap") {
        drawSpecularMapShader();
    }
    else if (m_shader->getName() == "lightsource") {
        drawLightShader();
	}
    else {
		std::cout << "Shader name not found in Cube draw : " << m_shader->getName() << std::endl;
    }

    m_mesh->draw();
}

void Cube::drawCubeShader() {
    m_shader->setVec3("viewPos", m_shader->getCamera()->getPosition());
    m_shader->setTexture("material.diffuse", m_texture->getID(), 0);
    m_shader->setVec3("material.specular", 0.75, 0.75, 0.75);
    m_shader->setFloat("material.shininess", 32.0f);
    m_shader->setVec3("light.position", m_light->getPos());
    m_shader->setVec3("light.ambient", 0.75f, 0.75f, 0.75f);
    m_shader->setVec3("light.diffuse", 1.0f, 1.0f, 1.0f); // darken diffuse light a bit
    m_shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
}

void Cube::drawSpecularMapShader() {
    if (!m_specularMap) {
        throw std::invalid_argument("Error: No specular map texture set for specularMap shader.");
        return;
	}
    m_shader->setVec3("viewPos", m_shader->getCamera()->getPosition());
    m_shader->setTexture("material.diffuse", m_texture->getID(), 0);
    m_shader->setTexture("material.specular", m_specularMap->getID(), 1);
    m_shader->setFloat("material.shininess", 32.0f);
    m_shader->setVec3("light.position", m_light->getPos());
    m_shader->setVec3("light.ambient", m_light->getAmbient());
    m_shader->setVec3("light.diffuse", m_light->getDiffuse()); // darken diffuse light a bit
    m_shader->setVec3("light.specular", m_light->getSpecular());
}


void Cube::drawLightShader() {
    m_shader->setVec3("lightColor", m_light->getLightColor());  // Associe la couleur au shader
}