#ifndef QCIRCLE_HPP
#define QCIRCLE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/String.hpp>

class QCircle {
public:
    QCircle(unsigned, unsigned, const sf::String&);
    virtual ~QCircle();
    auto run() -> void;

private:
    auto handleEvents() -> void;
    auto update() -> void;
    auto display() -> void;

private:
    unsigned width;
    unsigned height;
    sf::RenderWindow window;
    sf::VertexArray curve;
};

#endif // QCIRCLE_HPP