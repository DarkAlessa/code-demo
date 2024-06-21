#include "graph.hpp"
#include <cmath>

Graph::Graph(unsigned width, unsigned height, const sf::String& title)
:   window{sf::VideoMode(width, height), title} {
    window.setFramerateLimit(60);

    g_a.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
    g_a.resize(2 * 600);
    g_b.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
    g_b.resize(2 * 600);
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
    line[0].color = sf::Color{80, 80, 80, 255};
    line[1].color = sf::Color{80, 80, 80, 255};

    // Graph A
    for (float i = 0.0f; i < 600.0f; i++) {
        g_a[2 * i].position = sf::Vector2f(i, 180 + (80 * sin(i/24)));
        g_a[2 * i].color = sf::Color{128, 255, 0, 210};

        g_a[2 * i + 1].position = sf::Vector2f(i, 180.f);
        g_a[2 * i + 1].color = sf::Color{32, 32, 32, 0};
    }

    // Graph B
    for (float i = 0.0f; i < 600.0f; i++) {
        g_b[2 * i].position = sf::Vector2f(i, 180 + (120 * sin(i/24)));
        g_b[2 * i].color = sf::Color{120, 100, 20, 210};

        g_b[2 * i + 1].position = sf::Vector2f(i, 180.f);
        g_b[2 * i + 1].color = sf::Color{32, 32, 32, 0};
    }
}

auto Graph::display() -> void {
    window.clear(sf::Color(32, 32, 32, 255));
    window.draw(g_a);
    window.draw(g_b);
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