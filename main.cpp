#include "placing.h"
#include "rendering.h"
#include "simulating.h"

int main() {
  for (int i = 0; i < WIDTH; i++)
    for (int j = 0; j < HEIGHT; j++)
      map[i][j] = -1;

  // Font font("arialmt.ttf");

  cursor.setSize(Vector2f(cursor_scale * SCALE, cursor_scale * SCALE));
  cursor.setOutlineColor(Color::Black);
  cursor.setOutlineThickness(3);
  cursor.setFillColor(Color::Transparent);

  while (window.isOpen()) {
    getEvent();
    mouse = Mouse::getPosition(window) / SCALE;
    cursor.setPosition((Vector2f)(mouse * SCALE));
    if (Mouse::isButtonPressed(Mouse::Button::Left)) {
      if (isPlacing)
        place();
      else
        erase();
    }

    // fps
    // fps_text.setString(to_string((int)(1.0f / clock.restart().asSeconds())));
    simulate();
    display();
  }
}
