#include "placing.h"
#include "Grid.h"

using namespace sf;

void Placer::place() {

  for (int y = mouse.y; y < mouse.y + cursor_scale; y++)
    for (int x = mouse.x; x < mouse.x + cursor_scale; x++) {
      if (!grid.fits(x, y)) {
        continue;
      }
      if (grid.get(x, y).type == Types::empty) {
        grid.set(x, y, Cell(type));
        grid.set_chunk_awake_at(x, y, true);
      }
    }
}

void Placer::erase() {
  for (int y = mouse.y; y < mouse.y + cursor_scale; y++)
    for (int x = mouse.x; x < mouse.x + cursor_scale; x++) {
      if (!grid.fits(x, y))
        continue;
      if (grid.get(x, y).type != Types::empty) {
        grid.set(x, y, Cell());
        grid.set_chunk_awake_at(x, y, true);
      }
    }
}
