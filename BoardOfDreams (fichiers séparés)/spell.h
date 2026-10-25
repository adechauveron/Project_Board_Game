#pragma once
#include <vector>
#include "types.h"

bool in_spell_range(const entity& player, int x, int y);
void move_cursor(spell_overlay& spell, char direction, const grid& map, const entity& player);
bool cast_spell(std::vector<enemy>& creatures, int target_x, int target_y);
