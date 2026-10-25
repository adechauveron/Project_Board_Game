#include <iostream>
#include <cstdlib>
#include <ctime>
#include "types.h"
#include "map.h"
#include "display.h"
#include "game.h"

int main()
{
	srand(time(0));
	char input = 'p';
	storytime(input, 0); // Ecran de lancement + lore

	for (int current_level = 0; current_level < nb_levels; current_level++)
	{
		grid map;//initie la map
		std::vector<enemy> creatures;//initie les ennemis
		entity player{ 0, 0, player_char, levels[current_level].player_health };//initie le joueur

		if (!load_map(levels[current_level].map_file, map, player, creatures))
		{
			return -1;
		}

		int gamestate = level_playing(map, creatures, player);

		if (gamestate == 666) // le joueur est mort -> Game Over
		{
			system("cls");
			storytime('p', gamestate);
			return 666;
		}
		storytime(input, gamestate + current_level);
	}

	system("cls");
	std::cout << "Salvation Obtained !";
	return 10;
}
