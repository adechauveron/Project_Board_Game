#include <iostream>
#include <cstdlib>
#include <conio.h>
#include "display.h"
#include "map.h"
#include "entities.h"
#include "spell.h"

void showMap(const grid& map, const entity& player, const std::vector<enemy>& creatures, const spell_overlay& spell)
{
	for (int i = 0; i < map_height(map); i++) // i = ligne
	{
		for (int j = 0; j < map_width(map); j++) // j = colonne
		{
			if (spell.active && i == spell.cursor_x && j == spell.cursor_y)
			{
				std::cout << cursor_char << ' ';
			}
			else if (collidingenemy(creatures, i, j))
			{
				std::cout << enemy_char << ' ';
			}
			else if (i == player.coord_x && j == player.coord_y)
			{
				std::cout << player_char << ' ';
			}
			else if (spell.active && in_spell_range(player, i, j))
			{
				std::cout << range_char << ' ';
			}
			else
			{
				std::cout << get_tile_at(map, i, j).name << ' ';
			}
		}
		std::cout << std::endl;
	}
}

void storytime(char input, int player_state) // Textes d'histoire
{
	if (input == 'p' && player_state == 0)
	{
		std::cout << "BOARD OF DREAMS" << std::endl;
		std::cout << "This world is a dream among many" << std::endl;
		std::cout << "The darkness has won its first battle against the mind" << std::endl;
		std::cout << "Go onto the boards, find the exit, and obtain salvation !";
		input = _getch();
		system("cls");
	}
	else if (player_state == 1)
	{
		std::cout << "The temple of Heinshfault..." << std::endl;
		std::cout << "Be careful of the creatures here, one touch will be fatal..." << std::endl;
		input = _getch();
		system("cls");
	}
	else if (player_state == 2)
	{
		std::cout << "The mountains of Apocrypha..." << std::endl;
		std::cout << "Be careful of the cave inside, you might get ambushed !" << std::endl;
		std::cout << "The lava is unforgiving as well..." << std::endl;
		input = _getch();
		system("cls");
	}
	else if (player_state == 3)
	{
		std::cout << "The maze of Darraen..." << std::endl;
		std::cout << "Carefullness and patience might be your greatest ally..." << std::endl;
		input = _getch();
		system("cls");
	}
	else if (player_state == 4)
	{
		std::cout << "The lava fields of Saria..." << std::endl;
		std::cout << "Creatures are in their habitat, they care not for the dangerous heat..." << std::endl;
		input = _getch();
		system("cls");
	}
	else if (player_state == 5)
	{
		std::cout << "A sanctuary of peace, Finally some respite" << std::endl;
		std::cout << "You earned an additionnal point of health !" << std::endl;
		input = _getch();
		system("cls");
	}
	else if (player_state == 6)
	{
		std::cout << "The maze of Jaggar" << std::endl;
		std::cout << "I can only wish you good luck on your endeavours." << std::endl;
		input = _getch();
		system("cls");
	}
	else if (player_state == 7)
	{
		std::cout << "The maze of Varrion" << std::endl;
		std::cout << "You're growing closer to your goal, just a little bit more.." << std::endl;
		input = _getch();
		system("cls");
	}
	else if (player_state == 8)
	{
		std::cout << "Even this haven of peace has been ruined by this heat of destruction... I wish you good luck." << std::endl;
		std::cout << "You earned an additionnal point of health !" << std::endl;
		input = _getch();
		system("cls");
	}
	else if (player_state == 9)
	{
		std::cout << "The Maze of ##########, its name has been forgotten to the abyss of knowledge" << std::endl;
		std::cout << "The story is over, for both of you. May you find Salvation." << std::endl;
		input = _getch();
		system("cls");
	}
	else if (player_state == 666) // Game Over
	{
		std::cout << "And the world fell to darkness...";
	}
}
