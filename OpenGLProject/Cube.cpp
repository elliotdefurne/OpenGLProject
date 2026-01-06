#include "Cube.h"

#include "Vertex.h"   // Structure d'un sommet (position, couleur, texture…)
#include "Mesh.h"     // Classe pour gerer les buffers OpenGL et dessiner
#include "Shader.h"   // Classe pour les shaders OpenGL
#include "Texture.h"  // Classe pour les textures
#include "Transformation.h" // Classe pour position, rotation et scale
#include "LightSource.h"
#include "Player.h"
#include "LightManager.h"
#include "LightSource.h"
#include "Renderer.h"

Cube::Cube(glm::vec3 center, float edge, Shader* shader, Player* player)
    : m_center(center), m_edge(edge), m_shader(shader), m_player(player), m_lightManager(nullptr), m_lightSource(nullptr), m_renderer(nullptr) {
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
        Vertex(x - halfEdge, y - halfEdge, z + halfEdge, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f),
        Vertex(x + halfEdge, y - halfEdge, z + halfEdge, 0.0f,  0.0f, 1.0f, 1.0f, 0.0f),
        Vertex(x + halfEdge, y + halfEdge, z + halfEdge, 0.0f,  0.0f, 1.0f, 1.0f, 1.0f),
        Vertex(x - halfEdge, y + halfEdge, z + halfEdge, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f),

        // Face arrière (Z-)
        Vertex(x - halfEdge, y - halfEdge, z - halfEdge, 0.0f,  0.0f, -1.0f, 1.0f, 0.0f),
        Vertex(x + halfEdge, y - halfEdge, z - halfEdge, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f),
        Vertex(x + halfEdge, y + halfEdge, z - halfEdge, 0.0f,  0.0f, -1.0f, 0.0f, 1.0f),
        Vertex(x - halfEdge, y + halfEdge, z - halfEdge, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f),

        // Face gauche (X-)
        Vertex(x - halfEdge, y - halfEdge, z - halfEdge, -1.0f,  0.0f, 0.0f, 0.0f, 0.0f),
        Vertex(x - halfEdge, y - halfEdge, z + halfEdge, -1.0f,  0.0f, 0.0f, 1.0f, 0.0f),
        Vertex(x - halfEdge, y + halfEdge, z + halfEdge, -1.0f,  0.0f, 0.0f, 1.0f, 1.0f),
        Vertex(x - halfEdge, y + halfEdge, z - halfEdge, -1.0f,  0.0f, 0.0f, 0.0f, 1.0f),

        // Face droite (X+)
        Vertex(x + halfEdge, y - halfEdge, z - halfEdge, 1.0f,  0.0f, 0.0f, 1.0f, 0.0f),
        Vertex(x + halfEdge, y - halfEdge, z + halfEdge, 1.0f,  0.0f, 0.0f, 0.0f, 0.0f),
        Vertex(x + halfEdge, y + halfEdge, z + halfEdge, 1.0f,  0.0f, 0.0f, 0.0f, 1.0f),
        Vertex(x + halfEdge, y + halfEdge, z - halfEdge, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f),

        // Face du bas (Y-)
        Vertex(x - halfEdge, y - halfEdge, z - halfEdge, 0.0f,  -1.0f, 0.0f, 1.0f, 0.0f),
        Vertex(x + halfEdge, y - halfEdge, z - halfEdge, 0.0f,  -1.0f, 0.0f, 1.0f, 1.0f),
        Vertex(x + halfEdge, y - halfEdge, z + halfEdge, 0.0f,  -1.0f, 0.0f, 0.0f, 1.0f),
        Vertex(x - halfEdge, y - halfEdge, z + halfEdge, 0.0f,  -1.0f, 0.0f, 0.0f, 0.0f),

        // Face du haut (Y+)
        Vertex(x - halfEdge, y + halfEdge, z - halfEdge, 0.0f,  1.0f, 0.0f, 0.0f, 0.0f),
        Vertex(x + halfEdge, y + halfEdge, z - halfEdge, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f),
        Vertex(x + halfEdge, y + halfEdge, z + halfEdge, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f),
        Vertex(x - halfEdge, y + halfEdge, z + halfEdge, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f)
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
}

// Constructeur du cube
Cube::Cube(glm::vec3 center, float edge, Shader* shader, LightSource* lightSource, Player* player)
    : Cube(center, edge, shader, player) {
    m_lightSource = lightSource;
    m_mesh->load(m_vertices, m_indices, m_textures, (unsigned int)VertexAttribute::POSITION | (unsigned int)VertexAttribute::COLOR);
}

// Constructeur du cube
Cube::Cube(glm::vec3 center, float edge, Shader* shader, std::vector<Texture*> textures, Renderer* renderer, LightManager* lightManager, Player* player)
	: Cube(center, edge, shader, player) {
    m_textures = textures;
    m_lightManager = lightManager;
    m_renderer = renderer;
    m_mesh->load(m_vertices, m_indices, m_textures, (unsigned int)VertexAttribute::POSITION | (unsigned int)VertexAttribute::NORMAL | (unsigned int)VertexAttribute::TEXCOORD);
}

// Destructeur -> appelé quand on détruit l’objet Cube
// Libère la mémoire utilisée
Cube::~Cube() {
    m_vertices.clear();       // Vide la liste de sommets
    m_indices.clear();        // Vide la liste d’indices
    delete m_mesh;            // Détruit le mesh
    delete m_transformation;  // Détruit la transformation
}

inline std::vector<Texture*> Cube::getTextures() const {
    return m_mesh->getTextures();
}

// Prépare le cube pour être affiché (envoie les données au GPU)
void Cube::update() {
   
}

// Dessine le cube à l’écran
void Cube::draw() {
    m_shader->clearUniformLocations();                          // Nettoie les anciens réglages du shader
    m_shader->setModel(m_transformation->getMatrix());          // Envoie la matrice "modèle" (position/rotation/scale)
    m_shader->use();                                            // Active le shader
    m_shader->setupMatrices();                                  // Envoie la transformation complète


    if (m_shader->getName() == "lightsource") {
        drawLightSourceShader();
	}
    else if (m_shader->getName() == "severallights") {
        drawSeveralLightShader();
    }
    else {
		std::cout << "Shader name not found in Cube draw : " << m_shader->getName() << std::endl;
    }
    
    m_mesh->draw();
}

void Cube::drawLightSourceShader() {
    if (!m_lightSource) {
        throw std::invalid_argument("Error: Light not set.");
        return;
    }

    m_shader->setVec3("lightColor", m_lightSource->getLightColor());  // Associe la couleur au shader
}

void Cube::drawSeveralLightShader() {
    if (!m_player) {
        throw std::invalid_argument("Error: No camera set for Flashlight shader.");
        return;
    }

    m_shader->setVec3("viewPos", m_shader->getCamera()->getPosition());

	//printf("Number of textures in Cube drawSeveralLightShader: %zu\n", m_textures.size());

	for (Texture * texture : m_textures){
        if (!texture->hasSpecular()) {
            throw std::invalid_argument("Error: No specular map texture set for specularMap shader.");
            return;
        }
        texture->applyToShader(m_shader);
    }

    m_lightManager->applyToShader(m_shader);
}