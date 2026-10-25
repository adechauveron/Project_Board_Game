#pragma once
#include <vector>
#include "types.h"

void showMap(const grid& map, const entity& player, const std::vector<enemy>& creatures, const spell_overlay& spell = spell_overlay{}); // valeur par défaut : uniquement ici
void storytime(char input, int player_state);
