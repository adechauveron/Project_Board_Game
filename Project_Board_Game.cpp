#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <curses.h>
#include <panel.h>

static const int x = 10;
static const int y = 20;
<<<<<<< Updated upstream
=======
static const int nb_enemies = 5;
static const int spell_range = 1;  
static const int spell_damage = 1;
>>>>>>> Stashed changes

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
	int current_x;
	int current_y;
};

struct position_cursor
{
	int coord_x;
	int coord_y;
};

struct tile
{
	char name;
	int indice;
	bool traversal;
	bool win_cond = false;
};
<<<<<<< Updated upstream
=======

struct level
{
	std::string map_file;
	entity player;
	enemy creatures[nb_enemies];
};

enum class player_state
{
	MOVE, 
	SPELL  
};

>>>>>>> Stashed changes
const tile water{ '~',1,false }; //Infos Tile Water
const tile mountain{ 'M',2, false };//Infos Tile Mountain
const tile ground{ '.',0, true,false };//Infos Tile Ground
const tile win{ 'E',3,true,true };
tile const tiles[4] = { ground, water, mountain, win }; //Tableau des différents types de Tiles

<<<<<<< Updated upstream
tile get_tile_at(int map[10][20], int x, int y)
=======
const level levels[] = {
	{
		"MAPS\\map1.txt",//Niveau 1
		{ 2,4,'H',1 },//joueur1
		{
			{1,8,'X',1,1},//créatures niveau1
			{8,2,'X',1,1},
			{8,17,'X',1,1},
			{1,1,'X',1,1},
			{5,10,'X',1,1}
		}
	},
	{
		"MAPS\\map2.txt",//Niveau 2
		{ 2,2,'H',2 },//joueur2
		{
			{2,8,'X',1,1},//créatures niveau2
			{8,3,'X',1,1},
			{8,18,'X',1,1},
			{1,8,'X',1,1},
			{6,9,'X',1,1}
		}
	}
};
const int nb_levels = sizeof(levels) / sizeof(levels[0]);
tile get_tile_at(int map[x][y], int coord_x, int coord_y) // Récupérer une tile aux coordonnées x et y
>>>>>>> Stashed changes
{
	int index = map[x][y];
	tile current_tile = tiles[index];
	return current_tile;
}

<<<<<<< Updated upstream
bool win_condition(entity& player, int map[10][20], int x, int y)
{
	tile win = get_tile_at(map, x, y);
	if (win.win_cond == true)
=======
bool win_condition(entity& player, int map[x][y], int coord_x, int coord_y) // vérifie la condition de victoire
{
	return get_tile_at(map, coord_x, coord_y).win_cond;
}

bool still_alive(const enemy& creature) // Un ennemi est vivant tant qu'il lui reste de la vie
{
	return creature.monster.health > 0;
}

bool collidingenemy(enemy creatures[nb_enemies], int coord_x, int coord_y) //Renvoie Vrai si un ennemi se trouve aux coordonnées x et y
{
	for (int current_m = 0; current_m < nb_enemies; current_m++)
>>>>>>> Stashed changes
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool collidingenemy(enemy creatures[5], int x, int y)
{
	for (int current_m = 0; current_m < 5; current_m++)
	{
		if (x == creatures[current_m].monster.coord_x && y == creatures[current_m].monster.coord_y)
		{
			return true;
		}
	}
	return false;
}

<<<<<<< Updated upstream
void losinghealth(entity& player, enemy creatures[5])
{
	for (int current_m = 0; current_m < 5; current_m++)
=======
void losinghealth(entity& player, enemy creatures[nb_enemies]) //Calcule les dégats après avoir touché un ennemi
{
	for (int current_m = 0; current_m < nb_enemies; current_m++)
>>>>>>> Stashed changes
	{
		if (collidingenemy(creatures, player.coord_x, player.coord_y) == true)
		{
<<<<<<< Updated upstream
			player.health -= creatures[current_m].damage;
=======
			if (still_alive(creatures[current_m]) && player.coord_x == creatures[current_m].monster.coord_x && player.coord_y == creatures[current_m].monster.coord_y)
			{
				player.health -= creatures[current_m].damage;
			}
>>>>>>> Stashed changes
		}
	}
}

<<<<<<< Updated upstream
void afficherMap(int map[10][20], entity player, enemy creatures[5]) // Affiche le plateau
=======
void showMap(int map[x][y], entity player, enemy creatures[nb_enemies], const position_cursor* cursor = nullptr) // Affiche le plateau
>>>>>>> Stashed changes
{
	for (int i = 0; i < x; i++) //i = ligne
	{
		for (int j = 0; j < y; j++) //j = colonne
		{
<<<<<<< Updated upstream
			bool spawnenemy = false;
			int enemyexist;

			for (int current_m = 0; current_m < 5; current_m++) //Place les monstres
=======
			int enemyexist = -1;
			for (int current_m = 0; current_m < nb_enemies; current_m++)
>>>>>>> Stashed changes
			{
				if (i == creatures[current_m].current_x && j == creatures[current_m].current_y)
				{
					spawnenemy = true;
					enemyexist = current_m;
				}
			}
<<<<<<< Updated upstream
			if (spawnenemy)
=======
			char symbol; // [MODIFIE] on choisit d'abord le symbole, on l'affiche ensuite
			if (enemyexist != -1) //Place les monstres
>>>>>>> Stashed changes
			{
				symbol = creatures[enemyexist].monster.name;
			}
			else if (i == player.coord_x && j == player.coord_y) //Place l'Avatar
			{
<<<<<<< Updated upstream
				std::cout << player.name << ' ';
			}
			else
			{
				for (int c = 0; c < 4; c++)
				{
					if (map[i][j] == tiles[c].indice) //Place les tiles
					{
						std::cout << tiles[c].name << ' ';
					}

				}
=======
				symbol = player.name; //Place l'Avatar
			}
			else if (cursor != nullptr && abs(i - player.coord_x) + abs(j - player.coord_y) <= spell_range)
			{
				symbol = '*';
			}
			else
			{
				symbol = tiles[map[i][j]].name; //Place les tiles
>>>>>>> Stashed changes
			}
			std::cout << symbol<<' ';
		}
		std::cout << std::endl;
	}
}

<<<<<<< Updated upstream
void player_choice(entity& player, char choice, int map[10][20])//Prend les Input du Joueur
{
	if (choice == 'z' && player.coord_x > 0)
	{
		tile Next_tile = get_tile_at(map, player.coord_x - 1, player.coord_y);
		if (Next_tile.traversal)
		{
			player.coord_x -= 1;
=======
bool get_direction(char touch, int& directionx, int& directiony)
{
	directionx = 0;
	directiony = 0;

	switch (touch)
	{
		case 'z':
		{
			directionx = -1;
			return true;
		}
		case 's': 
		{ 
			directionx = 1;  
			return true; 
		}
		case 'q':
		{
			directiony = -1;
			return true;
		}
		case 'd':
		{
			directiony = 1;
			return true;
		}
		default:
		{ 
			return false; 
		}
	}
}
void move_entity(entity& entity, char direction, int map[x][y], enemy* creatures = nullptr)
{
	int directionx;
	int directiony;
	if (!get_direction(direction, directionx, directiony))
	{
		return;
	}
	
	int movement_x = entity.coord_x + directionx;
	int movement_y = entity.coord_y + directiony;

	if (movement_x < 0 || movement_x >= x || movement_y < 0 || movement_y >= y) //vérifie si le movement est hors du plateau
	{
		return;
	}
	if (!get_tile_at(map, movement_x, movement_y).traversal) // vérifie si la tile est non traversable
	{
		return;
	}
	if (creatures != nullptr && collidingenemy(creatures, movement_x, movement_y)) // vérifie si la case est déjà occupée par un ennemi
	{
		return;
	}

	entity.coord_x = movement_x;
	entity.coord_y = movement_y;
}

void move_cursor(position_cursor& cursor, char direction, const entity& player)
{
	int directionx, directiony;
	if (!get_direction(direction, directionx, directiony))
	{
		return;
	}

	int new_x = cursor.coord_x + directionx;
	int new_y = cursor.coord_y + directiony;

	if (new_x < 0 || new_x >= x || new_y < 0 || new_y >= y) // hors du plateau
	{
		return;
	}
	int distance = abs(new_x - player.coord_x) + abs(new_y - player.coord_y);

	if (distance > spell_range) // hors de portée
	{
		return;
	}

	cursor.coord_x = new_x;
	cursor.coord_y = new_y;
}

void cast_spell(const position_cursor& cursor, enemy creatures[nb_enemies])
{
	for (int current_m = 0; current_m < nb_enemies; current_m++)
	{
		if (still_alive(creatures[current_m]) && cursor.coord_x == creatures[current_m].monster.coord_x && cursor.coord_y == creatures[current_m].monster.coord_y)
		{
			creatures[current_m].monster.health -= spell_damage;
		}
	}
}

void creaturesMove(enemy creatures[nb_enemies], int map[x][y])//Deplacement ennemis (aléatoire)
{
	static const char directions[4] = { 'z', 's', 'q', 'd' };
	for (int current_m = 0; current_m < nb_enemies; current_m++)
	{
		if (still_alive(creatures[current_m])) // [MODIFIE] un ennemi mort ne bouge plus
		{
			move_entity(creatures[current_m].monster, directions[rand() % 4], map, creatures); //utilse move_entity en revoyant un char au hasard
		}
	}
}

void storytime(char input, int player_state) // L'histoire qui se lance au début du jeu
{
	if (input == 'p' && player_state == 0) //L'histoire est affichée jusqu'à ce que le joueur presse une touche
	{
		std::cout << "BOARD OF DREAMS" << std::endl;
		std::cout << "This world is a dream among many" << std::endl;
		std::cout << "The darkness has won its first battle against the mind" << std::endl;
		std::cout << "Go onto the boards, find the exit, and obtain salvation !";
		input = _getch();
		system("cls");
	}
	else if (player_state == 666) //Game Over
	{
		std::cout << "And the world fell to darkness...";
	}
}

bool load_map(const std::string& maps, int map[x][y])
{
	std::ifstream file_is_open(maps); //lit le fichier
	if (!file_is_open) //La fonction n'arrive pas à lire le fichier texte
	{
		std::cout << "Impossible d'ouvrir " << maps << std::endl;
		return false;
	}

	std::string line; //Initie la ligne de texte
	for (int i = 0; i < x; i++)
	{
		if (!std::getline(file_is_open, line) || line.size() < y) //verifie s'il peut pas atteindre la ligne et si la taille de la ligne est correcte
		{
			std::cout << "Ligne " << i << " invalide ou trop courte" << std::endl;
			return false;
>>>>>>> Stashed changes
		}
	}
	else if (choice == 's' && player.coord_x < 9)
	{
		{
			tile Next_tile = get_tile_at(map, player.coord_x + 1, player.coord_y);
			if (Next_tile.traversal)
			{
<<<<<<< Updated upstream
				player.coord_x += 1;
			}
		}
	}
	else if (choice == 'q' && player.coord_y > 0)
	{
		tile Next_tile = get_tile_at(map, player.coord_x, player.coord_y - 1);
		if (Next_tile.traversal)
=======
				if (line[j] == tiles[c].name)
				{
					value = tiles[c].indice;
				}
			}

			if (value == -1)
			{
				std::cout << "Caractère inconnu '" << line[j]
					<< "' ligne " << i << ", colonne " << j << std::endl;
				return false;
			}
			map[i][j] = value;
		}
	}
	return true;
}

int level_playing(int map[x][y], enemy* creatures, entity player) //Lance le level
{
	player_state state = player_state::MOVE; 
	position_cursor cursor{ player.coord_x, player.coord_y }; 

	while (win_condition(player, map, player.coord_x, player.coord_y) == false) //Tant que la case Win n'est pas atteinte la boucle de jeu continue !
	{
		showMap(map, player, creatures, state == player_state::SPELL ? &cursor : nullptr); 

		if (state == player_state::MOVE)
			std::cout << std::endl << "[z q s d] deplacer   [c] sort" << std::endl;
		else
			std::cout << std::endl << "[z q s d] curseur   [c] lancer   [v] annuler" << std::endl;

		char input = _getch();
		bool turn_played = false; 

		switch (state)
		{
		case player_state::MOVE:
			if (input == 'c') // MOVE -> SPELL : le curseur démarre sur le joueur
			{
				cursor = { player.coord_x, player.coord_y };
				state = player_state::SPELL;
			}
			else
			{
				move_entity(player, input, map);
				turn_played = true;
			}
			break;

		case player_state::SPELL:
			if (input == 'c') // lancer le sort : SPELL -> MOVE, le tour est utilisé
			{
				cast_spell(cursor, creatures);
				state = player_state::MOVE;
				turn_played = true;
			}
			else if (input == 'v') // annuler : SPELL -> MOVE, sans utiliser le tour
			{
				state = player_state::MOVE;
			}
			else
			{
				move_cursor(cursor, input, player);
			}
			break;
		}

		if (turn_played)
		{
			losinghealth(player, creatures);
			creaturesMove(creatures, map);
			losinghealth(player, creatures);
		}

		system("cls");
		if (player.health <= 0)
>>>>>>> Stashed changes
		{
			player.coord_y -= 1;
		}
	}

	else if (choice == 'd' && player.coord_y < 19)
	{
		tile Next_tile = get_tile_at(map, player.coord_x, player.coord_y + 1);
		if (Next_tile.traversal)
		{
			player.coord_y += 1;
		}

	}
}


void creaturesM(enemy creatures[5], int map[10][20])//Deplacement ennemis
{
	int block = 0;
	int random = rand() % 4;
	for (int current_m = 0; current_m < 5; current_m++)
	{
		if (random == 0 && creatures[current_m].monster.coord_x > 0)
		{
			tile Next_tile = get_tile_at(map, creatures[current_m].monster.coord_x - 1, creatures[current_m].monster.coord_y);
			if (Next_tile.traversal)
			{
				if (collidingenemy(creatures, creatures[current_m].monster.coord_x - 1, creatures[current_m].monster.coord_y) == false)
				{
					creatures[current_m].current_x -= 1;
				}
			}
		}
		else if (random == 1 && creatures[current_m].monster.coord_x < 9)
		{
			tile Next_tile = get_tile_at(map, creatures[current_m].monster.coord_x + 1, creatures[current_m].monster.coord_y);
			if (Next_tile.traversal)
			{
				if (collidingenemy(creatures, creatures[current_m].monster.coord_x - 1, creatures[current_m].monster.coord_y) == false)
				{
					creatures[current_m].current_x += 1;
				}

			}
		}
		else if (random == 2 && creatures[current_m].monster.coord_y > 0)
		{
			tile Next_tile = get_tile_at(map, creatures[current_m].monster.coord_x, creatures[current_m].monster.coord_y - 1);
			if (Next_tile.traversal)
			{
				if (collidingenemy(creatures, creatures[current_m].monster.coord_x, creatures[current_m].monster.coord_y - 1) == false)
				{
					creatures[current_m].current_y -= 1;
				}
			}
		}
		else if (random == 0 && creatures[current_m].monster.coord_y < 19)
		{
			tile Next_tile = get_tile_at(map, creatures[current_m].monster.coord_x, creatures[current_m].monster.coord_y + 1);
			if (Next_tile.traversal)
			{
				if (collidingenemy(creatures, creatures[current_m].monster.coord_x, creatures[current_m].monster.coord_y + 1) == false)
				{
					creatures[current_m].current_y += 1;
				}

			}
		}
	}
}
void creatures_update(enemy creatures[5])
{
	for (int current_m = 0; current_m < 5; current_m++)
	{
		creatures[current_m].monster.coord_x = creatures[current_m].current_x;
		creatures[current_m].monster.coord_y = creatures[current_m].current_y;
	}
}

WINDOW* creation_display_ncurses(int height, int width, int start_y, int start_x);

int main(int argc, char* argv[])
{
	srand(time(0));
<<<<<<< Updated upstream
	bool InGame = true;	int map1[10][20] = //Premier niveau du jeu
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,2,2,2,3,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};
	int map2[10][20] = //Deuxième niveau du jeu
	{
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{2,0,0,0,1,0,0,2,2,2,2,2,2,0,0,0,0,0,0,1},
	{2,0,0,0,1,0,0,1,1,1,3,1,1,0,0,0,0,0,0,1},
	{2,0,2,2,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{2,0,2,2,2,0,0,2,2,2,2,2,2,0,0,0,0,0,0,1},
	{2,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};
	enemy creatures[5] = {
		{1,8,'X',1,1,1,8},
		{8,2 ,'X',1,1,8,2},
		{8,17,'X',1,1,8,17},
		{1,1 ,'X',1,1,1,1},
		{5,10,'X',1,1,5,10}
	}; //Infos ennemies lvl 1
	enemy creatures2[5] = {
		{2,8,'X',1,1,2,8},
		{8,3 ,'X',1,1,8,3},
		{8,15,'X',1,1,8,15},
		{1,8 ,'X',1,1,1,8},
		{3,10,'X',1,1,3,10}
	};// Infos ennemis lvl2 2
	entity player{ 2,4,'H',1 }; //Infos Joueur lvl 1
	entity player2{ 2,2,'H',1 }; //Infos Joueur lvl 2
	char input;
	
	WINDOW* affichage;
	int start_x, start_y, width, height;
	int ch;
	initscr();// Initie ncurses
	cbreak();

	start_color();
	height = 10;
	width = 30;
	start_x = (COLS - width) / 2;
	start_y = 0;
	refresh();

	affichage = creation_display_ncurses(height, width, start_x, start_y);

	while (player.health != 0)//boucle du jeu
	{
	
		wrefresh(affichage);
		while (win_condition(player, map1, player.coord_x, player.coord_y) == false)
		{
			
			afficherMap(map1, player, creatures);
			std::cout << "Ordonner votre avatar : ";
			std::cin >> input;
			player_choice(player, input, map1);
			losinghealth(player, creatures);
			creaturesM(creatures, map1);
			creatures_update(creatures);
			losinghealth(player, creatures);
			system("cls");
			if (player.health <= 0)
			{
				system("cls");
				std::cout << "GAME OVER" << '\n' << "Vous avez perdu la partie !" << '\n';
			}
		}
		while (win_condition(player2, map2, player2.coord_x, player2.coord_y) == false)
		{
			afficherMap(map2, player2, creatures2);
			std::cout << "Ordonner votre avatar : ";
			std::cin >> input;
			player_choice(player2, input, map2);
			losinghealth(player2, creatures2);
			creaturesM(creatures2, map2);
			creatures_update(creatures2);
			losinghealth(player2, creatures2);
			system("cls");
			if (player2.health <= 0)
			{
				player.health = player2.health;
				system("cls");
				std::cout << "GAME OVER" << '\n' << "Vous avez perdu la partie !" << '\n';
			}

		}
		if (win_condition(player2, map2, player2.coord_x, player2.coord_y) == true)
		{
			std::cout << "you win";
			player.health = -1;
			return -1;
		}
	}
	endwin();
	return 0;
}
WINDOW* creation_display_ncurses(int height, int width, int start_y, int startx)
{
	WINDOW* local_win;

	local_win = newwin(height, width, start_y, startx);
	box(local_win, 0, 0);

	wrefresh(local_win);

	return local_win;
}

=======
	char input = 'p';//Initie l'input qui va lancer le storytime
	storytime(input,0); //Ecran de lancement + Lore 
	for (int current_level = 0; current_level < nb_levels; current_level++) // les niveaux s'enchainent
{
	int map[x][y];
	if (!load_map(levels[current_level].map_file, map))
		return -1;

	enemy creatures[nb_enemies];
	for (int i = 0; i < nb_enemies; i++)
	{
		creatures[i] = levels[current_level].creatures[i];
	}

	int gamestate = level_playing(map, creatures, levels[current_level].player);

	if (gamestate == 666) // le joueur est mort -> Game Over
	{
		system("cls");
		storytime('p', gamestate);
		return 666;
	}

}

system("cls");
std::cout << "Salvation Obtained" << std::endl;
std::cout << "Was it worth the chase" << std::endl;
return 42;
}
>>>>>>> Stashed changes
