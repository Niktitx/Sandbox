#include "rendering.h"
#include "Grid.h"
#include <SFML/Graphics/RenderWindow.hpp>

void Renderer::render() {
  sf::VertexArray pixels(sf::PrimitiveType::Triangles, WIDTH * HEIGHT * 6);

  for (int i = 0; i < WIDTH * HEIGHT; ++i) {
    const auto c = grid.get(i);
    if (c.type == Types::empty)
      continue;
    float px = (i % WIDTH) * SCALE;
    float py = i / WIDTH * SCALE;

    int v = i * 6;
    pixels[v + 0].position = {px, py};
    pixels[v + 1].position = {px + SCALE, py};
    pixels[v + 2].position = {px + SCALE, py + SCALE};
    pixels[v + 3].position = {px, py};
    pixels[v + 4].position = {px + SCALE, py + SCALE};
    pixels[v + 5].position = {px, py + SCALE};

    for (int j = 0; j < 6; j++)
      pixels[v + j].color = getColor[c.color];
  }
  window.draw(pixels);
}

void Renderer::display() {
  window.clear(sf::Color::White);
  render();
  window.draw(cursor);
  window.display();
}
