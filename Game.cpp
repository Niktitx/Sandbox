#include "Game.h"
#include "Grid.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>

void Game::process_input() {
  mouse = sf::Mouse::getPosition(renderer.window) / SCALE;
  cursor.setPosition((sf::Vector2f)(mouse * SCALE));

  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
    if (placer.isPlacing)
      placer.place();
    else
      placer.erase();
  }
}

void Game::get_event() {
  while (const std::optional event = renderer.window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      renderer.window.close();
    }
    if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      using sf::Keyboard::Scancode;
      if (placer.key_to_place.find(keyPressed->scancode) !=
          placer.key_to_place.end()) {
        placer.isPlacing = true;
        placer.type = placer.key_to_place[keyPressed->scancode];
      } else
        switch (keyPressed->scancode) {
        case Scancode::Escape:
          renderer.window.close();
          break;
        case Scancode::R:
          grid.reset();
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
          placer.isPlacing = false;
          break;
        }
    }
  }
  mouse = Mouse::getPosition(renderer.window);
  cursor.setPosition(Vector2f(mouse));
  mouse /= SCALE;

  if (Mouse::isButtonPressed(Mouse::Button::Left)) {
    if (placer.isPlacing)
      placer.place();
    else
      placer.erase();
  }
}

void Game::run() {
  while (renderer.window.isOpen()) {
    get_event();
    simulation.simulate();
    renderer.display();
  }
}
