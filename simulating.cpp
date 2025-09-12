#include "simulating.h"
#include "Cell.h"
#include "base.h"
#include <queue>

#include <iostream>

void update_neighbour(int x, int y) {
  if (fits(x, y) && map[x][y] != -1)
    needUpdate.push(map[x][y]);
}

void move(Cell &cell, int new_x, int new_y) {
  int x = cell.position.x, y = cell.position.y;
  update_neighbour(x + 1, y);
  update_neighbour(x - 1, y);
  update_neighbour(x, y + 1);
  update_neighbour(x, y - 1);
  update_neighbour(x + 1, y + 1);
  update_neighbour(x - 1, y + 1);
  update_neighbour(x + 1, y - 1);
  update_neighbour(x - 1, y - 1);
  std::swap(map[cell.position.x][cell.position.y], map[new_x][new_y]);
  cell.position.y = new_y;
  cell.position.x = new_x;
  needUpdate.push(map[new_x][new_y]);
}

void updateSand(Cell &cell) {
  int x = cell.position.x, y = cell.position.y;
  if (y + 1 >= HEIGHT)
    return;
  if (map[x][y + 1] == -1) {
    move(cell, x, y + 1);
  } else {

    bool fits_left = x - 1 >= 0;
    bool fits_right = x + 1 < WIDTH;

    bool free_left =
        fits_left && map[x - 1][y] == -1 && map[x - 1][y + 1] == -1;
    bool free_right =
        fits_right && map[x + 1][y] == -1 && map[x + 1][y + 1] == -1;

    if (free_right && free_left) {
      if (random() % 2 == 0)
        move(cell, x + 1, y + 1);
      else
        move(cell, x - 1, y + 1);
    } else if (free_left)
      move(cell, x - 1, y + 1);
    else if (free_right)
      move(cell, x + 1, y + 1);
  }
}

// after erasing IDs changing and it doesn't work :(
void simulate() {
  std::queue<int> update = needUpdate;
  while (!(update.empty())) {
    auto &u = units[update.front()];
    switch (u.type) {
    case solid:
      break;
    case sand:
      updateSand(u);
      break;
    }
    update.pop();
    needUpdate.pop();
  }
}
