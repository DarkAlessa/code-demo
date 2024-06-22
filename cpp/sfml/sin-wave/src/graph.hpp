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
    sf::VertexArray g_a;
    sf::VertexArray g_b;
    sf::VertexArray sine_wave_a;
    sf::VertexArray sine_wave_b;
    sf::Vertex line[2];
};

#endif // GRAPH_HPP
