#include "app.h"

int main(int argc, char** argv) {
    App app("Demo", 600, 600);
    app.set_texture("./assets/sprite/Sprite-0001.png");
    app.run();

    return 0;
}
