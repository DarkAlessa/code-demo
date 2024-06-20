#include "verlet.hpp"

Verlet::Verlet(unsigned width, unsigned height, const sf::String& title)
:   window{sf::VideoMode(width, height), title}
{
    window.setFramerateLimit(60);

    rec.setSize(sf::Vector2f(50, 50));
    rec.setFillColor(sf::Color::Green);
}

Verlet::~Verlet() = default;

auto Verlet::handleEvents() -> void {
    sf::Event event;
    while(window.pollEvent(event)) {
      if(event.type == sf::Event::Closed) {
        window.close();
        break;
      } 
    }
}

auto Verlet::update() -> void {
    //
}

auto Verlet::display() -> void {
    window.clear(sf::Color::Black);
    window.draw(rec);
    window.display();
}

auto Verlet::run() -> void {
    while (window.isOpen()) {
        handleEvents();
        update();
        display();
    }
}