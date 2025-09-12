#pragma once
#include "Cell.h"
#include <queue>

inline std::queue<int> needUpdate;

void update_neighbour(int x, int y);
void move(Cell &cell, int new_x, int new_y);
void simulate();
