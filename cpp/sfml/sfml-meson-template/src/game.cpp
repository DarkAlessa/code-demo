#include "game.hpp"

Game::Game(unsigned width, unsigned height, const sf::String& title)
:   window{sf::VideoMode(width, height), title, sf::Style::Default, sf::ContextSettings(24, 0, 0)}
{
    window.setFramerateLimit(60);

    rec.setSize(sf::Vector2f(50.0f, 50.0f));
    rec.setFillColor(sf::Color::Green);
    rec.setPosition(sf::Vector2f(50.0f, 50.0f));
}

Game::~Game() = default;

auto Game::handleEvents() -> void {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        break;
      } 
    }
}

auto Game::update() -> void {
    //
}

auto Game::display() -> void {
    window.clear(sf::Color(40, 40, 40, 255));
    window.draw(rec);
    window.display();
}

auto Game::run() -> void {
    while (window.isOpen()) {
        handleEvents();
        update();
        display();
    }
}