#include "graph.hpp"
#include <cmath>

Graph::Graph(unsigned width, unsigned height, const sf::String& title)
:   window{sf::VideoMode(width, height), title} {
    window.setFramerateLimit(60);

    g_a.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
    g_a.resize(2 * 600);
    g_b.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
    g_b.resize(2 * 600);
    sine_wave_a.setPrimitiveType(sf::PrimitiveType::LineStrip);
    sine_wave_a.resize(600);
    sine_wave_b.setPrimitiveType(sf::PrimitiveType::LineStrip);
    sine_wave_b.resize(600);
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
    for (float x = 0.0f; x < 600.0f; x++) {
        // Graph a
        g_a[2 * x].position = sf::Vector2f(x, 180.f + (80.f * sin(x * 0.04f + 0.0f)));
        g_a[2 * x].color = sf::Color{128, 255, 0, 255};
        g_a[2 * x + 1].position = sf::Vector2f(x, 180.f);
        g_a[2 * x + 1].color = sf::Color{32, 32, 32, 0};

        sine_wave_a[x].position = sf::Vector2f(x, 180.f + (80.f * sin(x * 0.04f + 0.0f))); 
        sine_wave_a[x].color = sf::Color::White;

        // Graph b
        g_b[2 * x].position = sf::Vector2f(x, 180.f + (120.f * sin(x * 0.04f + 0.0f)));
        g_b[2 * x].color = sf::Color{120, 100, 20, 255};
        g_b[2 * x + 1].position = sf::Vector2f(x, 180.f);
        g_b[2 * x + 1].color = sf::Color{32, 32, 32, 0};

        sine_wave_b[x].position = sf::Vector2f(x, 180.f + (120.f * sin(x * 0.04f + 0.0f))); 
        sine_wave_b[x].color = sf::Color::White;
    }
}

auto Graph::display() -> void {
    window.clear(sf::Color(32, 32, 32, 255));
    window.draw(g_a);
    window.draw(g_b);
    window.draw(sine_wave_a);
    window.draw(sine_wave_b);
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
