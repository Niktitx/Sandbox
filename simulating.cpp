#include "simulating.h"
#include "Grid.h"
#include <SFML/System/Vector2.hpp>
#include <map>

// 0 - Can't move
std::map<Types, int> density{{solid, 0},    {Types::empty, 0}, {sand, 10},
                             {water, 5},    {lava, 7},         {steam, 1},
                             {wet_sand, 10}};

void Simulation::add_reaction(Types t1, Types t2, Types r1, Types r2,
                              float chance) {

  reactionTable[(int)t1][(int)t2] = {true, r1, r2, chance};
  reactionTable[(int)t2][(int)t1] = {true, r2, r1, chance};
}

bool Simulation::check_reactions(int x, int y) {

  constexpr int dx[] = {1, -1, 0, 0};
  constexpr int dy[] = {0, 0, 1, -1};

  for (int i = 0; i < 4; i++) {
    Reaction r = reactionTable[(int)grid.get(x, y).type]
                              [(int)grid.get(x + dx[i], y + dy[i]).type];
    if (!r.happens)
      continue;
    if (dis(gen) > r.chance) {

      grid.set_chunk_awake_at(x, y, true);
      continue;
    }

    grid.set(x, y, Cell(r.resultA));
    grid.set(x + dx[i], y + dy[i], Cell(r.resultB));

    grid.set_chunk_awake_at(x, y, true);

    return true;
  }
  return false;
}

void Simulation::move(sf::Vector2i pos, sf::Vector2i new_pos) {
  grid.swap_cells(pos, new_pos);
  grid.set_chunk_awake_at(pos.x, pos.y, true);
  grid.set_updated(new_pos.x, new_pos.y, false);
}

bool Simulation::updateSand(int x, int y) {
  if (y + 1 >= HEIGHT)
    return false;
  if (grid.get(x, y + 1).type == Types::empty) {
    move({x, y}, {x, y + 1});
    return true;
  }

  bool fits_left = x - 1 >= 0;
  bool fits_right = x + 1 < WIDTH;

  bool free_left = fits_left && grid.get(x - 1, y).type == Types::empty &&
                   grid.get(x - 1, y + 1).type == Types::empty;
  bool free_right = fits_right && grid.get(x + 1, y).type == Types::empty &&
                    grid.get(x + 1, y + 1).type == Types::empty;

  if (free_right && free_left) {
    if (random() % 2 == 0)
      move({x, y}, {x + 1, y + 1});
    else
      move({x, y}, {x - 1, y + 1});
    return true;
  } else if (free_left) {
    move({x, y}, {x - 1, y + 1});
    return true;
  } else if (free_right) {
    move({x, y}, {x + 1, y + 1});
    return true;
  }

  return false;
}

void check_density(int x, int y, Grid &grid) {
  if (density[grid.get(x, y - 1).type] != 0 &&
      density[grid.get(x, y - 1).type] > density[grid.get(x, y).type]) {
    grid.swap_cells({x, y}, {x, y - 1});
    grid.set_updated(x, y, true);
    grid.set_updated(x, y - 1, true);
  }
}

void Simulation::updateLiquid(int x, int y, int dispersion_rate) {
  if (updateSand(x, y))
    return;

  check_density(x, y, grid);

  if (y + 1 >= HEIGHT)
    return;

  int dir = (rand() % 2 == 0) ? 1 : -1;
  auto tryFlowHorizontally = [&](int direction) -> bool {
    int targetX = x;
    for (int i = 1; i <= dispersion_rate; ++i) {
      int checkX = x + (i * direction);

      if (grid.get(checkX, y).type != Types::empty)
        break;

      targetX = checkX;
      if (grid.get(checkX, y + 1).type != Types::empty) {
        break;
      }
    }

    if (targetX != x) {
      grid.swap_cells({x, y}, {targetX, y});
      return true;
    }
    return false;
  };

  if (!tryFlowHorizontally(dir)) {
    tryFlowHorizontally(-dir);
  }
}

void Simulation::updateGas(int x, int y, int dispersion_rate) {
  check_density(x, y, grid);

  if (y - 1 < 0)
    return;

  int dir = (rand() % 2 == 0) ? 1 : -1;
  if (grid.get(x, y - 1).type == Types::empty) {
    move({x, y}, {x, y - 1});
    return;
  }

  bool fits_left = x - 1 >= 0;
  bool fits_right = x + 1 < WIDTH;

  bool free_left = fits_left && grid.get(x - 1, y).type == Types::empty &&
                   grid.get(x - 1, y - 1).type == Types::empty;
  bool free_right = fits_right && grid.get(x + 1, y).type == Types::empty &&
                    grid.get(x + 1, y - 1).type == Types::empty;

  if (free_right && free_left) {
    if (random() % 2 == 0)
      move({x, y}, {x + 1, y - 1});
    else
      move({x, y}, {x - 1, y - 1});
    return;
  } else if (free_left) {
    move({x, y}, {x - 1, y - 1});
    return;
  } else if (free_right) {
    move({x, y}, {x + 1, y - 1});
    return;
  }

  auto tryFlowHorizontally = [&](int direction) -> bool {
    int targetX = x;
    for (int i = 1; i <= dispersion_rate; ++i) {
      int checkX = x + (i * direction);

      if (grid.get(checkX, y).type != Types::empty)
        break;

      targetX = checkX;
      if (grid.get(checkX, y - 1).type != Types::empty) {
        break;
      }
    }

    if (targetX != x) {
      grid.swap_cells({x, y}, {targetX, y});
      return true;
    }
    return false;
  };

  if (!tryFlowHorizontally(dir)) {
    tryFlowHorizontally(-dir);
  }
}

void Simulation::simulate() {
  for (int cx = 0; cx < grid.chunksX; cx++)
    for (int cy = grid.chunksY - 1; cy >= 0; cy--) {
      if (!grid.is_chunk_awake(cx, cy))
        continue;
      grid.set_chunk_awake(cx, cy, false);
      for (int x = cx * CHUNK_SIZE; x < min((cx + 1) * CHUNK_SIZE, WIDTH); x++)
        for (int y = max((cy + 1) * CHUNK_SIZE - 1, 0); y >= cy * CHUNK_SIZE;
             y--) {
          Cell c = grid.get(x, y);
          // if (c.updated)
          //   continue;
          // grid.set_updated(x, y, true);
          switch (c.type) {
          case Types::empty:
          case solid:
          case border:
            continue;
          case sand:
          case wet_sand:
            updateSand(x, y);
            break;
          case water:
            updateLiquid(x, y, 20);
            break;
          case lava:
            updateLiquid(x, y, 1);
            break;
          case steam:
            updateGas(x, y, 20);
            break;
          }
          check_reactions(x, y);
        }
    }
}
