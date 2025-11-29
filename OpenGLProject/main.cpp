#include "Game.h"

/*
* TODO:
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