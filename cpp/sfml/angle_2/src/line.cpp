#include "line.h"

Line::Line(float x0, float y0, float x1, float y1)
: start(x0, y0), end(x1, y1)
{
    line[0] = {sf::Vertex(start)};
    line[1] = {sf::Vertex(end)};
}

Line::Line(sf::Vector2f x, sf::Vector2f y)
: start(x), end(y) 
{
    line[0] = {sf::Vertex(start)};
    line[1] = {sf::Vertex(end)};
}

Line& Line::setStart(float x0, float y0) {
    this->line[0].position.x = x0;
    this->line[0].position.y = y0;
    return *this;
}

Line& Line::setStart(sf::Vector2f start) {
    this->line[0].position = start;
    return *this;
}

Line& Line::setEnd(float x1, float y1) {
    this->line[1].position.x = x1;
    this->line[1].position.y = y1;
    return *this;
}

Line& Line::setEnd(sf::Vector2f end) {
    this->line[1].position = end;
    return *this;
}

Line& Line::setColor(sf::Color color) {
    this->line[0].color = color;
    this->line[1].color = color;
    return *this;
}

Line& Line::setColor(sf::Color colorA, sf::Color colorB) {
    this->line[0].color = colorA;
    this->line[1].color = colorB;
    return *this;
}

sf::Vertex* Line::getLine() {
    return line;
}

float Line::getStartX() {
    return line[0].position.x;
}

float Line::getStartY() {
    return line[0].position.y;
}

float Line::getEndX() {
    return line[1].position.x;
}

float Line::getEndY() {
    return line[1].position.y;
}

Line::~Line() = default;