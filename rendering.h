#pragma once

#include "base.h"
#include <SFML/Graphics/Text.hpp>
using namespace sf;

inline sf::RenderWindow window(sf::VideoMode({WIDTH * SCALE, HEIGHT *SCALE}),
                               "Sandbox");
void render();
void display();
inline RectangleShape cursor;
