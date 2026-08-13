#pragma once
#include "Grid.h"
#include <queue>
#include <random>

const int MAX_TYPES = 64;

struct Reaction {
  bool happens = false;
  Types resultA;
  Types resultB;
  float chance = 100;

  Reaction() {};
  Reaction(bool happens, Types resultA, Types resultB, float chance = 100)
      : happens(happens), resultA(resultA), resultB(resultB), chance(chance) {}
};

class Simulation {

  std::queue<int> needUpdate;
  void move(sf::Vector2i pos, sf::Vector2i new_pos);
  bool updateSand(int x, int y);
  void updateLiquid(int x, int y, int dispersion_rate);
  void updateGas(int x, int y, int dispersion_rate);
  Grid &grid;
  Reaction reactionTable[MAX_TYPES][MAX_TYPES];

  bool check_reactions(int x, int y);
  void add_reaction(Types t1, Types t2, Types r1, Types r2, float chance = 100);

  std::random_device rd;
  std::mt19937 gen;
  std::uniform_real_distribution<float> dis;

public:
  Simulation &operator=(const Simulation &other) {
    if (this == &other) {
      return *this;
    }
    grid = other.grid;
    return *this;
  }

  void add(Cell cell);
  void update_neighbour(int x, int y);
  Simulation(Grid &grid) : grid(grid) {

    gen = std::mt19937(rd());
    dis = std::uniform_real_distribution<float>(0.0f, 100.0f);
    for (int i = 0; i < MAX_TYPES; i++)
      for (int j = 0; j < MAX_TYPES; j++)
        reactionTable[i][j].happens = false;
    add_reaction(water, lava, steam, solid, 10);
    add_reaction(water, sand, water, wet_sand, 1);
    add_reaction(wet_sand, sand, wet_sand, wet_sand, 0.01);
    add_reaction(wet_sand, lava, sand, lava, 1);
    add_reaction(steam, Types::empty, water, Types::empty, 0.001);
  }
  Simulation();
  void simulate();
};
