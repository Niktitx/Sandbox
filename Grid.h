#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

constexpr int HEIGHT = 180, WIDTH = 320, SCALE = 5, CHUNK_SIZE = 32;

enum Types { border, empty, solid, sand, water, lava, steam, wet_sand };
inline const sf::Color getColor[]{
    sf::Color(89, 95, 99),    sf::Color(106, 113, 121),
    sf::Color(128, 142, 152), sf::Color(230, 216, 190),
    sf::Color(212, 189, 149), sf::Color(225, 210, 179),
    sf::Color(32, 126, 182),  sf::Color(63, 158, 204),
    sf::Color(1, 97, 158),    sf::Color(230, 156, 47),
    sf::Color(202, 66, 8),    sf::Color(206, 78, 13),
    sf::Color(203, 225, 239), sf::Color(187, 199, 206),
    sf::Color(148, 157, 163), sf::Color(170, 145, 114),
    sf::Color(145, 121, 97),  sf::Color(170, 148, 126)};

inline std::map<Types, int> type_offset{{solid, 0}, {sand, 1},  {water, 2},
                                        {lava, 3},  {steam, 4}, {wet_sand, 5}};

struct Cell {
  Types type;
  int color;
  bool updated = false;

  Cell(Types type);
  Cell() : type(Types::empty) {};
};

struct Chunk {
  bool isAwake = true;
};

class Grid {
  vector<Cell> grid;
  vector<Chunk> chunks;

public:
  int chunksX, chunksY;
  Grid() {
    grid.resize(WIDTH * HEIGHT);
    chunksX = (WIDTH + CHUNK_SIZE - 1) / CHUNK_SIZE;
    chunksY = (HEIGHT + CHUNK_SIZE - 1) / CHUNK_SIZE;

    chunks.resize(chunksX * chunksY);
  }
  bool fits(int x, int y);

  void set_chunk_awake(int cx, int cy, bool awake);
  void set_chunk_awake_at(int x, int y, bool awake);
  bool is_chunk_awake(int cx, int cy);

  void set_updated(int x, int y, bool updated);
  Cell get(int x, int y);
  Cell get(int i);
  void set(int x, int y, Cell cell);

  void reset();
  void swap_cells(sf::Vector2i a, sf::Vector2i b);
};
