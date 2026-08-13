#pragma once

#include "Grid.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class Renderer {

  void render();
  sf::RectangleShape &cursor;
  Grid &grid;

public:
  sf::RenderWindow window;

  Renderer &operator=(const Renderer &other) {
    if (this == &other) {
      return *this;
    }
    cursor = other.cursor;
    return *this;
  }

  Renderer(sf::RectangleShape &cursor, Grid &grid)
      : cursor(cursor), grid(grid) {
    window = sf::RenderWindow(sf::VideoMode({WIDTH * SCALE, HEIGHT * SCALE}),
                              "Sandbox");
  }
  void display();
};
