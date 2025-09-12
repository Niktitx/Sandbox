#include "Cell.h"
#include "base.h"
#include "simulating.h"
#include <cstdlib>
#include <map>
std::map<Types, int> type_offset{{solid, 0}, {sand, 1}, {water, 2}};
Cell::Cell(sf::Vector2i position, Types type) {
  // needUpdate = true;
  this->type = type;
  this->position = position;
  color = type_offset[type] * 3 + rand() % 3;
  needUpdate.push(map[position.x][position.y]);
}
