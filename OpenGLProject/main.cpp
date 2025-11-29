#include "Game.h"

/*
* TODO:
*   Changement classe texture (pour contenir specularMap) et donc textureManager
*   Classe Mesh
*   Enlever les couleurs des Vertex (uniquement position, normal, UV)
*   Collision (Hitbox)
*   Multi
*/

int main() {
    Game* game = new Game();

    game->run();

    delete game;
    
    return 0;
}