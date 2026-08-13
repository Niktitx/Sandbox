#pragma once

#include "Grid.h"
#include "simulating.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>

using namespace sf;
class Placer {

  Vector2i &mouse;
  int &cursor_scale;
  Grid &grid;
  Simulation &simulation;

public:
  Placer &operator=(const Placer &other) {
    if (this == &other) {
      return *this;
    }
    mouse = other.mouse;
    cursor_scale = other.cursor_scale;
    return *this;
  }

  Placer(Vector2i &mouse, int &cursor_scale, Grid &grid, Simulation &simulation)
      : mouse(mouse), cursor_scale(cursor_scale), grid(grid),
        simulation(simulation) {}
  Placer();

  std::unordered_map<sf::Keyboard::Scancode, Types> key_to_place{
      {Keyboard::Scancode::Num1, solid}, {Keyboard::Scancode::Num2, sand},
      {Keyboard::Scancode::Num3, water}, {Keyboard::Scancode::Num4, lava},
      {Keyboard::Scancode::Num5, steam},
  };

  Types type = solid;
  bool isPlacing = true;
  void place();
  void erase();
};
