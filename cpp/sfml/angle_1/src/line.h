#ifndef LINE_H
#define LINE_H

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

class Line {
public:
    Line(float, float, float, float);
    Line(sf::Vector2f, sf::Vector2f);
    virtual ~Line();

    Line& setStart(float, float);
    Line& setStart(sf::Vector2f);
    Line& setEnd(float, float);
    Line& setEnd(sf::Vector2f);
    Line& setColor(sf::Color);
    Line& setColor(sf::Color, sf::Color);

    float getStartX() const;
    float getStartY() const;
    float getEndX() const;
    float getEndY() const;
    const sf::Vertex* getLine() const;
    
private:
    sf::Vector2f start;
    sf::Vector2f end;
    sf::Vertex line[2];
};

#endif // LINE_H