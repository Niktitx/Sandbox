#pragma once
#include "Grid.h"
#include "placing.h"
#include "rendering.h"
#include "simulating.h"

class Game {
  Grid grid;
  sf::Vector2i mouse;
  sf::RectangleShape cursor;
  int cursor_scale = 4;

  Renderer renderer;
  Simulation simulation;
  Placer placer;
  void get_event();
  void process_input();

public:
  Game()
      : grid(), simulation(grid), placer(mouse, cursor_scale, grid, simulation),
        renderer(cursor, grid) {
    cursor.setSize(sf::Vector2f(cursor_scale * SCALE, cursor_scale * SCALE));
    cursor.setOutlineColor(sf::Color::Black);
    cursor.setOutlineThickness(3);
    cursor.setFillColor(sf::Color::Transparent);
  }

  void run();
};
