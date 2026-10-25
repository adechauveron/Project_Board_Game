#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>

using grid = std::vector<std::vector<int>>; //Vecteur de vecteurs (Tableau de tableaux) de int, représentant la map du niveau

struct entity
{
	int coord_x;
	int coord_y; 
	char name;
	int health;
};

struct enemy
{
	entity monster;
	int damage;
};

struct tile
{
	char name;
	int indice;
	bool traversal;
	bool win_cond = false;
	int damage = 0;
};

struct level
{
	std::string map_file;
	int player_health;
};

enum class play_state
{
	moving,     // le joueur se déplace 
	targeting   // le joueur choisit la case du sort avec le curseur 
};

struct spell_overlay
{
	bool active = false;
	int cursor_x = 0;
	int cursor_y = 0;
};

const char spell_key = 'e';        // touche pour ouvrir / confirmer le sort
const char cancel_key = 27;        // Echap : annule le sort
const int spell_range = 1;         // portée en carré autour du joueur
const char range_char = '*';
const char cursor_char = '^';

const char player_char = 'H';

const char enemy_char = 'X';
const int enemy_health = 1;
const int enemy_damage = 1;

const tile water{ '~', 1, false };
const tile mountain{ 'M', 2, false };
const tile ground{ '.', 0, true };
const tile win{ 'E', 3, true, true };
const tile lava{ '#', 4, true, false, 1 };

const int nb_tiles = 5;
const tile tiles[nb_tiles] = { ground, water, mountain, win, lava }; // l'indice dans le tableau = tile.indice

const level levels[] = {
	{ "MAPS\\map0.txt", 1 },
	{ "MAPS\\map1.txt", 1 },
	{ "MAPS\\map2.txt", 1 },
	{ "MAPS\\map3.txt", 1 },
	{ "MAPS\\map4.txt", 1 },
	{ "MAPS\\map5.txt", 2 },
	{ "MAPS\\map6.txt", 2 },
	{ "MAPS\\map7.txt", 2 },
	{ "MAPS\\map8.txt", 2 },
	{"MAPS\\map9.txt", 3 }
};
const int nb_levels = 10;



int map_height(const grid& map) 
{ 
	return static_cast<int>(map.size()); //hauteur de la map = nombre de lignes du tableau
}
int map_width(const grid& map) 
{ 
	return static_cast<int>(map[0].size()); //largeur de la map = nombre de colonnes du tableau (prend le nombre d'éléments de la première ligne)
}

tile get_tile_at(const grid& map, int coord_x, int coord_y)
{
	return tiles[map[coord_x][coord_y]];
}

bool win_condition(const grid& map, int coord_x, int coord_y) // vrai si le joueur est sur la case E
{
	return get_tile_at(map, coord_x, coord_y).win_cond;
}

bool collidingenemy(const std::vector<enemy>& creatures, int coord_x, int coord_y)
{
	for (const enemy& creature : creatures)
	{
		if (creature.monster.coord_x == coord_x && creature.monster.coord_y == coord_y)
		{
			return true;
		}
	}
	return false;
}
void take_tile_damage(entity& player, const grid& map)
{
	player.health -= get_tile_at(map, player.coord_x, player.coord_y).damage;
}

void losinghealth(entity& player, const std::vector<enemy>& creatures)
{
	for (const enemy& creature : creatures)
	{
		if (creature.monster.coord_x == player.coord_x && creature.monster.coord_y == player.coord_y)
		{
			player.health -= creature.damage;
		}
	}
}

bool in_spell_range(const entity& player, int x, int y)
{
	return (std::abs(x - player.coord_x) <= spell_range && std::abs(y - player.coord_y) <= spell_range);
}

void move_cursor(spell_overlay& spell, char direction, const grid& map, const entity& player)
{
	int new_x = spell.cursor_x;
	int new_y = spell.cursor_y;

	switch (direction)
	{
	case 'z':
		new_x -=1;
		break;
	case 's':
		new_x +=1; 
		break;
	case 'q': 
		new_y -=1; 
		break;
	case 'd': 
		new_y +=1; 
		break;
	default: 
		return;
	}

	bool outside = new_x < 0 || new_x >= map_height(map) || new_y < 0 || new_y >= map_width(map);
	if (outside || !in_spell_range(player, new_x, new_y))
	{
		return;
	}

	spell.cursor_x = new_x;
	spell.cursor_y = new_y;
}

bool cast_spell(std::vector<enemy>& creatures, int target_x, int target_y)
{
	for (std::vector<enemy>::iterator it = creatures.begin(); it != creatures.end(); ++it) //Parcourt le tableau dynamique creatures
	{
		if (it->monster.coord_x == target_x && it->monster.coord_y == target_y)
		{
			creatures.erase(it);
			return true;
		}
	}
	return false;
}

void showMap(const grid& map, const entity& player, const std::vector<enemy>& creatures, const spell_overlay& spell = spell_overlay{})
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

bool is_move_key(char c)
{
	return c == 'z' || c == 's' || c == 'q' || c == 'd';
}

void move_entity(entity& entity, char direction, const grid& map, const std::vector<enemy>* creatures = nullptr)
{
	int directionx = 0;
	int directiony = 0;

	switch (direction)
	{
	case 'z': 
		directionx = -1;
		break;
	case 's': 
		directionx = 1;
		break;
	case 'q': 
		directiony = -1; 
		break;
	case 'd': 
		directiony = 1; 
		break;
	default: 
		return;
	}

	int new_x = entity.coord_x + directionx;
	int new_y = entity.coord_y + directiony;

	bool outside = new_x < 0 || new_x >= map_height(map) || new_y < 0 || new_y >= map_width(map);
	if (outside)
	{
		return;
	}
	if (!get_tile_at(map, new_x, new_y).traversal)
	{
		return;
	}
	if (creatures != nullptr && collidingenemy(*creatures, new_x, new_y))
	{
		return;
	}

	entity.coord_x = new_x;
	entity.coord_y = new_y;
}

void creaturesMove(std::vector<enemy>& creatures, const grid& map) // Déplacement aléatoire des ennemis
{
	static const char directions[4] = { 'z', 's', 'q', 'd' };
	for (enemy& creature : creatures)
	{
		move_entity(creature.monster, directions[rand() % 4], map, &creatures);
	}
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

void end_turn(entity& player, std::vector<enemy>& creatures, const grid& map)
{
	take_tile_damage(player, map);
	losinghealth(player, creatures);
	creaturesMove(creatures, map);
	losinghealth(player, creatures);
}

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
