#include <iostream>
#include <cstdlib>
#include <conio.h>
#include "game.h"
#include "map.h"
#include "entities.h"
#include "spell.h"
#include "display.h"

int level_playing(const grid& map, std::vector<enemy>& creatures, entity player)
{
	play_state state = play_state::moving;
	spell_overlay spell;

	while (!win_condition(map, player.coord_x, player.coord_y)) // jusqu'à atteindre E
	{
		showMap(map, player, creatures, spell);

		if (state == play_state::moving)
		{
			std::cout << "\n[zqsd] Deplacement  [" << spell_key << "] Sort" << std::endl;
		}
		else
		{
			std::cout << "\n[zqsd] Curseur  [" << spell_key << "] Lancer  [Echap] Annuler" << std::endl;
		}

		char input = _getch();
		bool turn_ended = false;

		switch (state)
		{
		case play_state::moving:
			if (input == spell_key)
			{
				// Passage en mode ciblage : le curseur démarre sur le joueur
				state = play_state::targeting;
				spell.active = true;
				spell.cursor_x = player.coord_x;
				spell.cursor_y = player.coord_y;
			}
			else if (is_move_key(input))
			{
				move_entity(player, input, map);
				turn_ended = true;
			}
			break;

		case play_state::targeting:
			if (is_move_key(input))
			{
				move_cursor(spell, input, map, player);
			}
			else if (input == spell_key)
			{
				cast_spell(creatures, spell.cursor_x, spell.cursor_y);
				spell.active = false;
				state = play_state::moving;
				turn_ended = true;
			}
			else if (input == cancel_key)
			{
				spell.active = false;
				state = play_state::moving;
			}
			break;
		}

		if (turn_ended)
		{
			end_turn(player, creatures, map);
		}

		system("cls");
		if (player.health <= 0)
		{
			return 666;
		}
	}
	return 1;
}
