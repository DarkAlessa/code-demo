#include "verlet.h"

int main(int argc, char** argv) {
    Verlet verlet("verlet", 800, 600);
    verlet.run();
    return 0;
}
