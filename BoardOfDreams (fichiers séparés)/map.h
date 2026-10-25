#pragma once
#include <string>
#include <vector>
#include "types.h"

int map_height(const grid& map);
int map_width(const grid& map);
tile get_tile_at(const grid& map, int coord_x, int coord_y);
bool win_condition(const grid& map, int coord_x, int coord_y);
int find_tile_index(char c);
bool read_lines(const std::string& access, std::vector<std::string>& lines);
bool load_map(const std::string& access, grid& map, entity& player, std::vector<enemy>& creatures);
