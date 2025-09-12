#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

const int HEIGHT = 180, WIDTH = 320, SCALE = 5;
inline int map[WIDTH][HEIGHT];

inline sf::Vector2i mouse;
inline int cursor_scale = 4;
bool fits(int x, int y);
