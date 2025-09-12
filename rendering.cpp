#include "rendering.h"
#include "Cell.h"

void render() {
  VertexArray pixels(PrimitiveType::Triangles, units.size() * 6);

  for (int i = 0; i < units.size(); ++i) {
    const auto &u = units[i];
    float px = u.position.x * SCALE;
    float py = u.position.y * SCALE;

    int v = i * 6;
    pixels[v + 0].position = {px, py};
    pixels[v + 1].position = {px + SCALE, py};
    pixels[v + 2].position = {px + SCALE, py + SCALE};
    pixels[v + 3].position = {px, py};
    pixels[v + 4].position = {px + SCALE, py + SCALE};
    pixels[v + 5].position = {px, py + SCALE};

    for (int j = 0; j < 6; j++)
      pixels[v + j].color = getColor[u.color];
  }
  window.draw(pixels);
}

void display() {
  window.clear(Color::White);
  render();
  window.draw(cursor);
  window.display();
}
