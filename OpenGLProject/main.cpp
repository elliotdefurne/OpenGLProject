#include "Game.h"

/*
* TODO:
    Classe Parallelepipede rectangle
    Collision (Hitbox)
    Multi
*/

int main() {
    Game* game = new Game();

    game->run();

    delete game;
    
    return 0;
}