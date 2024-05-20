#include "game.h"

int main(int argc, char** argv) {
    Game* game = new Game("Demo", 800, 600);
    game->run();
    delete game;
    
    return 0;
}
