#include "app.h"

const int WIDTH  = 800;
const int HEIGHT = 600;

int main(int argc, char** argv) {
    App app("Demo", WIDTH, HEIGHT);
    app.set_texture("./assets/sprite/Sprite-0001.png");
    app.run();

    return 0;
}
