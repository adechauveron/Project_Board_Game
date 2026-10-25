#include <iostream>
#include <fstream>
#include "map.h"

int map_height(const grid& map)
{
	return static_cast<int>(map.size()); //hauteur de la map = nombre de lignes du tableau
}

int map_width(const grid& map)
{
	return static_cast<int>(map[0].size()); //largeur de la map = nombre d'éléments de la première ligne
}

tile get_tile_at(const grid& map, int coord_x, int coord_y)
{
	return tiles[map[coord_x][coord_y]];
}

bool win_condition(const grid& map, int coord_x, int coord_y) // vrai si le joueur est sur la case E
{
	return get_tile_at(map, coord_x, coord_y).win_cond;
}

int find_tile_index(char c) // Renvoie l'indice de la tile correspondant au caractère, ou -1 si le caractère est inconnu
{
	for (int i = 0; i < nb_tiles; i++)
	{
		if (tiles[i].name == c)
		{
			return tiles[i].indice;
		}
	}
	return -1;
}

bool read_lines(const std::string& access, std::vector<std::string>& lines) // Lit le fichier texte : une ligne du fichier = une ligne de 'lines'
{
	std::ifstream file(access);
	if (!file)
	{
		std::cout << "Impossible d'ouvrir " << access << std::endl;
		return false;
	}

	std::string line;
	while (std::getline(file, line))
	{
		if (!line.empty())
		{
			lines.push_back(line);
		}
	}

	if (lines.empty())
	{
		std::cout << "Fichier vide : " << access << std::endl;
		return false;
	}
	return true;
}

bool load_map(const std::string& access, grid& map, entity& player, std::vector<enemy>& creatures)//Transforme le fichier texte en tableau de int
{
	std::vector<std::string> lines;
	if (!read_lines(access, lines))
	{
		return false;
	}

	int height = static_cast<int>(lines.size());
	int width = static_cast<int>(lines[0].size());
	map.assign(height, std::vector<int>(width, ground.indice));
	creatures.clear();

	bool player_found = false;
	bool exit_found = false;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			char c = lines[i][j];

			if (c == player_char)
			{
				player_found = true;
				player.coord_x = i;
				player.coord_y = j;
			}
			else if (c == enemy_char)
			{
				enemy creature{ { i, j, enemy_char, enemy_health }, enemy_damage };
				creatures.push_back(creature);
			}
			else
			{
				int index = find_tile_index(c);
				if (tiles[index].win_cond)
				{
					exit_found = true;
				}
				map[i][j] = index;
			}
		}
	}
	return true;
}
