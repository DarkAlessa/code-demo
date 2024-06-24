#include "quarter-circle.hpp"
#include <cmath>

QCircle::QCircle(unsigned width, unsigned height, const sf::String& title)
:   window{sf::VideoMode(width, height), title, sf::Style::Default, sf::ContextSettings(24, 0, 4)}
{
    window.setFramerateLimit(60);

    curve.setPrimitiveType(sf::PrimitiveType::TriangleFan);
    curve.resize(91 + 1);
    curve[0].position = sf::Vector2f(80.f, 80.f);
    curve[0].color = sf::Color::Transparent;
}

QCircle::~QCircle() = default;

auto QCircle::handleEvents() -> void {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        break;
      } 
    }
}

struct Offset {
    float x;
    float y;
};

struct Quadrants {
    inline static float one = 0.f;
    inline static float two = 90.f;
    inline static float three = 180.f;
    inline static float four = 270.f;
};

auto QCircle::update() -> void {
    const Offset offset(80.f, 80.f);
    const float radius = 80.f;
    constexpr auto to_radian = 3.14159f / 180;
    int index = 1;
    for (float angle = 0.f; angle <= 90.f; angle++) {
        curve[index].position = sf::Vector2f(offset.x + (radius * cos((angle + Quadrants::one) * to_radian)),
                                             offset.y - (radius * sin((angle + Quadrants::one) * to_radian)));
        curve[index++].color = sf::Color::White;
    }
}

auto QCircle::display() -> void {
    window.clear(sf::Color(40, 40, 40, 255));
    window.draw(curve);
    window.display();
}

auto QCircle::run() -> void {
    while (window.isOpen()) {
        handleEvents();
        update();
        display();
    }
}