#include "placing.h"
#include "Cell.h"
#include "base.h"
#include "rendering.h"
#include "simulating.h"
#include <algorithm>
#include <optional>

using namespace sf;

void place() {
  for (int y = mouse.y; y < mouse.y + cursor_scale; y++)
    for (int x = mouse.x; x < mouse.x + cursor_scale; x++) {
      if (!fits(x, y))
        continue;
      if (map[x][y] == -1) {
        map[x][y] = units.size();
        units.push_back(Cell(Vector2i(x, y), type));
      }
    }
}

void erase() {
  for (int y = mouse.y; y < mouse.y + cursor_scale; y++)
    for (int x = mouse.x; x < mouse.x + cursor_scale; x++) {
      if (!fits(x, y))
        continue;
      if (map[x][y] != -1) {
        int id = map[x][y];
        units.erase(units.begin() + id);
        for (int i = id; i < units.size(); i++)
          map[units[i].position.x][units[i].position.y]--;

        map[x][y] = -1;
      }
    }
  for (int x = mouse.x - 1; x < mouse.x + cursor_scale + 1; x++) {
    update_neighbour(x, mouse.y - 1);
    update_neighbour(x, mouse.y + cursor_scale);
  }
  for (int y = mouse.y; y < mouse.y + cursor_scale; y++) {
    update_neighbour(mouse.x - 1, y);
    update_neighbour(mouse.x + cursor_scale, y);
  }
}

void getEvent() {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }
    if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      using sf::Keyboard::Scancode;
      if (key_to_place.find(keyPressed->scancode) != key_to_place.end()) {
        isPlacing = true;
        type = key_to_place[keyPressed->scancode];
      } else
        switch (keyPressed->scancode) {
        case Scancode::Escape:
          window.close();
          break;
        case Scancode::R:
          for (int i = 0; i < WIDTH; i++)
            for (int j = 0; j < HEIGHT; j++)
              map[i][j] = -1;

          units.clear();
          break;
        case Scancode::Equal:
          cursor_scale++;
          cursor.setSize(Vector2f(cursor_scale * SCALE, cursor_scale * SCALE));
          break;
        case Scancode::Hyphen:
          cursor_scale--;
          cursor_scale = std::max(1, cursor_scale);
          cursor.setSize(Vector2f(cursor_scale * SCALE, cursor_scale * SCALE));
          break;
        case Scancode::Num0:
          isPlacing = false;
          break;
        }
    }
  }
}
