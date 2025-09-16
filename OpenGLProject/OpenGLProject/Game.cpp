#include "Game.h"

/**
 * @class Game
 * @brief Classe principale qui g�re la boucle du jeu.
 *
 * Cette classe s'occupe de :
 * - Initialiser les biblioth�ques externes (GLFW, OpenGL...).
 * - Cr�er la fen�tre et le contexte de rendu.
 * - Lancer la boucle principale du jeu (update + render).
 * - Nettoyer correctement les ressources � la fermeture.
 */
Game::Game() : m_window(nullptr), m_renderer(nullptr) {
    // Initialisation de GLFW (librairie qui g�re fen�tre, inputs, contexte OpenGL)
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    Initialize();
}

/**
 * @brief Destructeur du jeu : lib�re la m�moire et ferme GLFW.
 *
 * En C++, le destructeur est appel� automatiquement quand l�objet sort de port�e.
 * Ici, on s�assure de lib�rer la m�moire pour �viter les fuites
 * (fen�tre, renderer, textures), puis on termine GLFW proprement.
 */
Game::~Game() {
    if (m_window) {
        delete m_window;
    }
    if (m_renderer) {
        delete m_renderer;
    }
    if (m_textureManager) {
        delete m_textureManager;
    }
    glfwTerminate();
}

/**
 * @brief Initialise les composants du jeu.
 *
 * �tapes principales :
 * 1. Cr�e la fen�tre (classe Window).
 * 2. Cr�e le moteur de rendu (Renderer).
 * 3. Cr�e le gestionnaire de textures (TextureManager).
 * 4. Configure OpenGL pour activer la 3D (test de profondeur, face culling...).
 */
void Game::Initialize() {
    m_window = new Window(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, Constants::WINDOW_TITLE);
    m_renderer = new Renderer();
    m_textureManager = new TextureManager();

    // Active le test de profondeur : permet de savoir quels objets sont devant
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Nettoie le buffer couleur et profondeur au d�marrage
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Optionnel : supprime le rendu des faces arri�re des objets (culling)
    // glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    // glFrontFace(GL_CCW);  // D�finit le sens des faces avant (anti-horaire)
}

/**
 * @brief Lance la boucle principale du jeu.
 *
 * Boucle classique d�un moteur de jeu :
 * - UPDATE : met � jour la logique (mouvements, collisions, IA...).
 * - RENDER : dessine la sc�ne � l��cran.
 * La boucle continue jusqu�� ce que la fen�tre soit ferm�e.
 */
void Game::Run() {
    while (!m_window->getShouldClose()) {
        // Gestion du framerate
        m_renderer->handleFrameTiming();

        // Logique du jeu
        Update();

        // Rendu graphique
        m_renderer->clear();
        Render();

        // Mise � jour de la fen�tre (swap buffers + gestion events)
        m_window->update();
    }
}

/**
 * @brief Met � jour la logique du jeu.
 *
 * Ici, tu mettras les d�placements des personnages, gestion d�entr�es clavier,
 * collisions, IA, scripts... Pour l�instant, elle est vide.
 */
void Game::Update() {
    // Update game logic here
}

/**
 * @brief G�re le rendu 3D de la sc�ne.
 *
 * �tapes principales :
 * 1. R�cup�re une texture via le TextureManager.
 * 2. D�finit un cube en 3D avec coordonn�es de texture.
 * 3. D�finit les indices (ordre de dessin des sommets).
 * 4. Charge le mesh avec vertices + indices + texture.
 * 5. Cr�e un shader basique (vertex + fragment).
 * 6. Applique une rotation continue au cube en fonction du temps.
 * 7. Active le shader, associe la texture et dessine le cube.
 */
void Game::Render() {
    Texture* texture = m_textureManager->getTexture(0);

    // D�finition d�un cube 3D avec coordonn�es (position, couleur, UV)
    std::vector<Vertex> cubeVertices = {
        // Face avant
        Vertex(-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
        Vertex(0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
        Vertex(0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f),
        Vertex(-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f),

        // Face arri�re
        Vertex(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f),
        Vertex(0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f),
        Vertex(0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.0f, 0.0f, 1.0f),
        Vertex(-0.5f,  0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f),

        // Face gauche
        Vertex(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.5f, 0.0f, 0.0f),
        Vertex(-0.5f, -0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f),
        Vertex(-0.5f,  0.5f,  0.5f, 0.0f, 0.5f, 1.0f, 1.0f, 1.0f),
        Vertex(-0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.5f, 0.0f, 1.0f),

        // Face droite
        Vertex(0.5f, -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f),
        Vertex(0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.5f, 0.0f, 0.0f),
        Vertex(0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
        Vertex(0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f),

        // Face du bas
        Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f),
        Vertex(0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f),
        Vertex(0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f),
        Vertex(-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f),

        // Face du haut
        Vertex(-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f),
        Vertex(0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f),
        Vertex(0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f),
        Vertex(-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f)
    };

    // Ordre des sommets � dessiner (2 triangles par face)
    std::vector<unsigned int> cubeIndices = {
        0, 1, 2,   2, 3, 0,     // Face avant
        4, 5, 6,   6, 7, 4,     // Face arri�re
        8, 9, 10,  10, 11, 8,   // Face gauche
        12, 13, 14, 14, 15, 12, // Face droite
        16, 17, 18, 18, 19, 16, // Face bas
        20, 21, 22, 22, 23, 20  // Face haut
    };

    // Cr�ation du mesh (objet 3D)
    Mesh mesh;
    mesh.load(cubeVertices, cubeIndices, texture);

    // Chargement du shader basique
    Shader basic("./res/shaders/basic.vert", "./res/shaders/basic.frag", true);

    // Matrice mod�le (transformations appliqu�es � l�objet)
    glm::mat4 model = glm::mat4(1.0f);
    float currentTime = static_cast<float>(glfwGetTime());


    // Exemple : rotation autour de l'axe X
    Transformation rotationX(glm::vec3(1.0f, 0.0f, 0.0f), currentTime * 50.0f);

    // Exemple : rotation autour de l'axe Y
    Transformation rotationY(glm::vec3(0.0f, 1.0f, 0.0f), currentTime * 30.0f);

    // Exemple : rotation autour de l'axe Z
    Transformation rotationZ(glm::vec3(0.0f, 0.0f, 1.0f), currentTime * 20.0f);

    // Tu combines les matrices en multipliant (ordre important en OpenGL)
    model = rotationZ.getMatrix() * rotationY.getMatrix() * rotationX.getMatrix();

    // Application de la transformation + texture + dessin
    basic.setModel(model);
    basic.use();
    basic.setTexture("ourTexture", texture->getID());

    mesh.draw();
}
