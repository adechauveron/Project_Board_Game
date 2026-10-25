#pragma once
#include <vector>
#include "types.h"

bool collidingenemy(const std::vector<enemy>& creatures, int coord_x, int coord_y);
void take_tile_damage(entity& player, const grid& map);
void losinghealth(entity& player, const std::vector<enemy>& creatures);
bool is_move_key(char c);
void move_entity(entity& entity, char direction, const grid& map, const std::vector<enemy>* creatures = nullptr); // valeur par défaut : uniquement ici
void creaturesMove(std::vector<enemy>& creatures, const grid& map);
void end_turn(entity& player, std::vector<enemy>& creatures, const grid& map);
