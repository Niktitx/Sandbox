#pragma once

#include "Cell.h"
#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>

using namespace sf;
inline std::unordered_map<sf::Keyboard::Scancode, Types> key_to_place{
    {Keyboard::Scancode::Num1, solid},
    {Keyboard::Scancode::Num2, sand},
    {Keyboard::Scancode::Num3, water},
};
inline Types type = solid;
inline bool isPlacing = true;
void place();
void erase();
void getEvent();
