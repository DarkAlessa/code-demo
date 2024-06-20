#ifndef VIRLET_HPP
#define VIRLET_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/String.hpp>

class Verlet {
public:
    Verlet(unsigned, unsigned, const sf::String&);
    virtual ~Verlet();
    auto run() -> void;

private:
    auto handleEvents() -> void;
    auto update() -> void;
    auto display() -> void;

private:
    unsigned width;
    unsigned height;
    sf::RenderWindow window;
    sf::RectangleShape rec;
};

#endif // VIRLET_HPP