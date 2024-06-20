#include "verlet.hpp"

auto main() -> int {
	Verlet verlet(600, 600, "Verlet");
	verlet.run();
}
