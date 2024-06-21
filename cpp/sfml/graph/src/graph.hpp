#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/String.hpp>

class Graph {
public:
    Graph(unsigned, unsigned, const sf::String&);
    virtual ~Graph();
    auto run() -> void;

private:
    auto handleEvents() -> void;
    auto update() -> void;
    auto display() -> void;

private:
    unsigned width;
    unsigned height;
    sf::RenderWindow window;

    sf::VertexArray gg;
    sf::Vertex line[2];
};

#endif // GRAPH_HPP