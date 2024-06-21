#include "graph.hpp"
#include <cmath>

Graph::Graph(unsigned width, unsigned height, const sf::String& title)
:   window{sf::VideoMode(width, height), title} {
    window.setFramerateLimit(60);

    gg.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
    gg.resize(2 * 600);
}

Graph::~Graph() = default;

auto Graph::handleEvents() -> void {
    sf::Event event;
    while(window.pollEvent(event)) {
      if(event.type == sf::Event::Closed) {
        window.close();
        break;
      } 
    }
}

auto Graph::update() -> void {
    line[0] = sf::Vertex(sf::Vector2f(0.f, 180.f));
    line[1] = sf::Vertex(sf::Vector2f(600.f, 180.f));
    line[0].color = sf::Color{120, 120, 120, 255};
    line[1].color = sf::Color{120, 120, 120, 255};

    for (float i = 0.0f; i < 600.0f; i++) {
        gg[2 * i].position = sf::Vector2f(i, 180 + (80 * sin(i/24)));
        gg[2 * i].color = sf::Color{128, 255, 0, 180};

        gg[2 * i + 1].position = sf::Vector2f(i, 180.f);
        gg[2 * i + 1].color = sf::Color{32, 32, 32, 0};
    }
}

auto Graph::display() -> void {
    window.clear(sf::Color(32, 32, 32, 255));
    window.draw(gg);
    window.draw(line, 2, sf::Lines);
    window.display();
}

auto Graph::run() -> void {
    while (window.isOpen()) {
        handleEvents();
        update();
        display();
    }
}