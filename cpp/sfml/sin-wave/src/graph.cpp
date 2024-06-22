#include "graph.hpp"
#include <cmath>

Graph::Graph(unsigned width, unsigned height, const sf::String& title)
:   window{sf::VideoMode(width, height), title} {
    window.setFramerateLimit(60);

    area_a.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
    area_a.resize(2 * 600);
    area_b.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
    area_b.resize(2 * 600);
    sine_wave_a.setPrimitiveType(sf::PrimitiveType::LineStrip);
    sine_wave_a.resize(600);
    sine_wave_b.setPrimitiveType(sf::PrimitiveType::LineStrip);
    sine_wave_b.resize(600);

    sf::Clock clock;
    sf::Time elapsed;
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

    static float phase = 0.f;
    static float amplitude = 0.f;

    // Graph A
    for (float x = 0.0f; x < 600.0f; x++) {
        float y_a = 180.f + (60.f * sin(x * 0.04f + phase));
        float y_b = 180.f + (amplitude * sin(x * 0.04f + 0.0f));

        // Graph a
        area_a[2 * x].position = sf::Vector2f(x, y_a);
        area_a[2 * x].color = sf::Color{128, 255, 0, 255};
        area_a[2 * x + 1].position = sf::Vector2f(x, 180.f);
        area_a[2 * x + 1].color = sf::Color{32, 32, 32, 0};

        sine_wave_a[x].position = sf::Vector2f(x, y_a);
        sine_wave_a[x].color = sf::Color::White;

        // Graph b
        area_b[2 * x].position = sf::Vector2f(x, y_b);
        area_b[2 * x].color = sf::Color{120, 100, 20, 255};
        area_b[2 * x + 1].position = sf::Vector2f(x, 180.f);
        area_b[2 * x + 1].color = sf::Color{32, 32, 32, 0};

        sine_wave_b[x].position = sf::Vector2f(x, y_b); 
        sine_wave_b[x].color = sf::Color::White;
    }

    static bool toggle = true;
    elapsed = clock.getElapsedTime();
    if (elapsed.asMilliseconds() > 60) {
        phase += 1.0f;
        if (phase >= 360.f)
            phase = 0.f;

        if (toggle == true) {
            amplitude += 8.f;
            if (amplitude >= 120.f)
                toggle = false;
        } else {
            amplitude -= 8.f;
            if (amplitude <= -120)
                toggle = true;
        }

        clock.restart();
    }
}

auto Graph::display() -> void {
    window.clear(sf::Color(40, 40, 40, 255));
    window.draw(area_a);
    window.draw(sine_wave_a);
    window.draw(area_b);
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
