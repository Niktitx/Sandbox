#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <unordered_map>
#include <vector>

enum Types { solid, sand, water };
inline const sf::Color getColor[]{
    sf::Color(89, 95, 99),   sf::Color(106, 113, 121), sf::Color(128, 142, 152),
    sf::Color(166, 126, 74), sf::Color(141, 101, 47),  sf::Color(178, 137, 79)};
/*inline std::unordered_map<Types, std::array<sf::Color, 3>> getColor{
    {solid,
     {sf::Color(89, 95, 99), sf::Color(106, 113, 121),
      sf::Color(128, 142, 152)}},
    {sand,
     {sf::Color(166, 126, 74), sf::Color(141, 101, 47),
      sf::Color(178, 137, 79)}},
};
*/

struct Cell {
  Types type;
  // bool needUpdate;
  sf::Vector2i position;
  int color;

  Cell(sf::Vector2i position, Types type);
};

inline std::vector<Cell> units;
