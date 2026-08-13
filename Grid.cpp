#include "Grid.h"

bool Grid::fits(int x, int y) {
  return x < WIDTH && x >= 0 && y < HEIGHT && y >= 0;
}

Cell Grid::get(int x, int y) {
  if (!fits(x, y))
    return Cell(border);
  return grid[y * WIDTH + x];
}

Cell Grid::get(int i) {
  if (i < 0 || i >= WIDTH * HEIGHT)
    return Cell(border);
  return grid[i];
}

void Grid::set(int x, int y, Cell cell) {
  if (!fits(x, y))
    return;
  cell.updated = false;
  grid[y * WIDTH + x] = cell;
}

void Grid::reset() { std::fill(grid.begin(), grid.end(), Cell()); }

void Grid::swap_cells(sf::Vector2i a, sf::Vector2i b) {
  if (fits(a.x, a.y) && fits(b.x, b.y))
    std::swap(grid[a.y * WIDTH + a.x], grid[b.y * WIDTH + b.x]);
  set_chunk_awake_at(a.x, a.y, true);
}

Cell::Cell(Types type) {
  this->type = type;
  color = type_offset[type] * 3 + rand() % 3;
}

void Grid::set_chunk_awake(int cx, int cy, bool awake) {
  if (cx >= 0 && cx < chunksX && cy >= 0 && cy < chunksY)
    chunks[cy * chunksX + cx].isAwake = awake;
}

void Grid::set_chunk_awake_at(int x, int y, bool awake) {
  int cx = x / CHUNK_SIZE;
  int cy = y / CHUNK_SIZE;
  set_chunk_awake(cx, cy, awake);
  if (!awake)
    return;
  if (x % CHUNK_SIZE == 0)
    set_chunk_awake(cx - 1, cy, awake);
  if (x % CHUNK_SIZE == CHUNK_SIZE - 1)
    set_chunk_awake(cx + 1, cy, awake);
  if (y % CHUNK_SIZE == 0)
    set_chunk_awake(cx, cy - 1, awake);
  if (y % CHUNK_SIZE == CHUNK_SIZE - 1)
    set_chunk_awake(cx, cy + 1, awake);
}

bool Grid::is_chunk_awake(int cx, int cy) {
  return chunks[cx + cy * chunksX].isAwake;
}

void Grid::set_updated(int x, int y, bool updated) {
  if (fits(x, y))
    grid[x + y * WIDTH].updated = updated;
}
