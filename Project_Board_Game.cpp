#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <conio.h>

static const int x = 10;
static const int y = 20;

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
};

const tile water{ '~',1,false }; //Infos Tile Water
const tile mountain{ 'M',2, false };//Infos Tile Mountain
const tile ground{ '.',0, true,false};//Infos Tile Ground
const tile win{'E',3,true,true}; // Infos Tile Win
tile const tiles[4] = { ground, water, mountain, win}; //Tableau des différents types de Tiles
tile get_tile_at(int map[x][y], int coord_x, int coord_y) // Récupérer une tile aux coordonnées x et y
{
	int index = map[coord_x][coord_y];
	tile current_tile = tiles[index];
	return current_tile;
} 
bool win_condition(entity& player, int map[x][y], int coord_x, int coord_y) // vérifie la condition de victoire (atteindre E)
{
	tile win = get_tile_at(map, coord_x, coord_y);
	if (win.win_cond == true)
	{
		return true;
	}
	else
	{
		return false;
	}
} 
bool collidingenemy(enemy creatures[5], int coord_x, int coord_y) //Renvoie Vrai si un ennemi se trouve aux coordonnées x et y
{
	for (int current_m = 0; current_m < 5; current_m++)
	{
		if (coord_x == creatures[current_m].monster.coord_x && coord_y == creatures[current_m].monster.coord_y)
		{
			return true;
		}
	}
	return false;
}
void losinghealth(entity& player, enemy creatures[5]) //Calcule les dégats après avoir touché un ennemi
{
	for (int current_m = 0; current_m < 5; current_m++)
	{
		if (collidingenemy(creatures, player.coord_x, player.coord_y))
		{
			player.health -= creatures[current_m].damage;
		}
	}
}
void afficherMap(int map[x][y], entity player, enemy creatures[5]) // Affiche le plateau
{
	for (int i = 0; i < x; i++) //i = ligne
	{
		for (int j = 0; j < y; j++) //j = colonne
		{
			bool spawnenemy = false;
			int enemyexist;

			for (int current_m = 0; current_m < 5; current_m++)
			{
				if (i == creatures[current_m].monster.coord_x && j == creatures[current_m].monster.coord_y)
				{
					spawnenemy = true;
					enemyexist = current_m;
				}
			}
			if (spawnenemy)  //Place les monstres
			{
				std::cout << creatures[enemyexist].monster.name << ' ';
			}
			else if (i == player.coord_x && j == player.coord_y) 
			{
				std::cout << player.name << ' '; //Place l'Avatar
			}
			else
			{
				for (int c = 0; c < 4; c++)
				{
					if (map[i][j] == tiles[c].indice) 
					{
						std::cout << tiles[c].name << ' '; //Place les tiles
					}

				}
			}
		}
		std::cout << std::endl;
	}
}
void player_choice(entity& player, char choice, int map[x][y])//Prend les Input du Joueur et les interprète en déplacements
{
	if (choice == 'z' && player.coord_x > x-x)
	{
		tile Next_tile = get_tile_at(map, player.coord_x - 1, player.coord_y);
		if (Next_tile.traversal)
		{
			player.coord_x --;
		}
	}
	else if (choice == 's' && player.coord_x < x-1)
	{
		{
			tile Next_tile = get_tile_at(map, player.coord_x + 1, player.coord_y);
			if (Next_tile.traversal)
			{
				player.coord_x ++;
			}
		}
	}
	else if (choice == 'q' && player.coord_y > y-y)
	{
		tile Next_tile = get_tile_at(map, player.coord_x, player.coord_y - 1);
		if (Next_tile.traversal)
		{
			player.coord_y --;
		}
	}

	else if (choice == 'd' && player.coord_y < y-1)
	{
		tile Next_tile = get_tile_at(map, player.coord_x, player.coord_y + 1);
		if (Next_tile.traversal)
		{
			player.coord_y ++;
		}

	}
}
void creaturesM(enemy creatures[5], int map[x][y])//Deplacement ennemis (aléatoire)
{
	for (int current_m = 0; current_m < 5; current_m++)
	{
		int random = rand() % 4;
		if (random == 0 && creatures[current_m].monster.coord_x > x-x)
		{
			tile Next_tile = get_tile_at(map, creatures[current_m].monster.coord_x - 1, creatures[current_m].monster.coord_y);
			if (Next_tile.traversal)
			{
				if (!collidingenemy(creatures, creatures[current_m].monster.coord_x - 1, creatures[current_m].monster.coord_y))
				{
					creatures[current_m].monster.coord_x --;
				}
			}
		}
		else if (random == 1 && creatures[current_m].monster.coord_x < x-1)
		{
			tile Next_tile = get_tile_at(map, creatures[current_m].monster.coord_x + 1, creatures[current_m].monster.coord_y);
			if (Next_tile.traversal)
			{
				if (!collidingenemy(creatures, creatures[current_m].monster.coord_x + 1, creatures[current_m].monster.coord_y))
				{
					creatures[current_m].monster.coord_x ++;
				}

			}
		}
		else if (random == 2 && creatures[current_m].monster.coord_y > y-y)
		{
			tile Next_tile = get_tile_at(map, creatures[current_m].monster.coord_x, creatures[current_m].monster.coord_y - 1);
			if (Next_tile.traversal)
			{
				if (!collidingenemy(creatures, creatures[current_m].monster.coord_x, creatures[current_m].monster.coord_y - 1))
				{
					creatures[current_m].monster.coord_y --;
				}
			}
		}
		else if (random == 3 && creatures[current_m].monster.coord_y < x-1)
		{
			tile Next_tile = get_tile_at(map, creatures[current_m].monster.coord_x, creatures[current_m].monster.coord_y + 1);
			if (Next_tile.traversal)
			{
				if (!collidingenemy(creatures, creatures[current_m].monster.coord_x, creatures[current_m].monster.coord_y + 1))
				{
					creatures[current_m].monster.coord_y ++;
				}

			}
		}
	}
}
void storytime(char input, int player_state) // L'histoire qui se lance au début du jeu
{
	if (input == 'p' && player_state == 0)
	{
		std::cout << "BOARD OF DREAMS" << '\n';
		std::cout << "This world is a dream among many" << '\n';
		std::cout << "The darkness has won its first battle against the mind" << '\n';
		std::cout << "Go onto the boards, find the exit, and you will get salvation !";
		input = _getch();
		system("cls");
	}
	else if (player_state == 666)
	{
		std::cout << "And the world fell to darkness...";
	}
}
bool load_map(const std::string& maps, int map[x][y])
{
	std::ifstream file(maps); //lit le fichier
	if (!file) //La fonction n'arrive pas à lire le fichier texte
	{
		std::cout << "Impossible d'ouvrir " << maps << '\n';
		return false;
	}

	std::string line; //Initie la ligne de texte
	for (int i = 0; i < x; i++) 
	{
		if (!std::getline(file, line) || line.size() < y) //verifie s'il peut pas atteindre la ligne et si la taille de la ligne est correcte
		{
			std::cout << "Ligne " << i << " invalide ou trop courte\n";
			return false;
		}

		for (int j = 0; j < y; j++)
		{
			int value = -1; //initie une valeur pour remplir le tableau de Int
			for (int c = 0; c < 4; c++)
			{
				if (line[j] == tiles[c].name)
					value = tiles[c].indice;
			}

			if (value == -1)
			{
				std::cout << "Caractère inconnu '" << line[j]
					<< "' ligne " << i << ", colonne " << j << '\n';
				return false;
			}
			map[i][j] = value;
		}
	}
	return true;
}

int level_playing(int map[x][y], enemy *creatures, entity player, char input) //Lance le level
{
	while (win_condition(player, map, player.coord_x, player.coord_y) == false)
	{
		afficherMap(map, player, creatures);
		input = _getch();
		player_choice(player, input, map);
		losinghealth(player, creatures);
		creaturesM(creatures, map);
		losinghealth(player, creatures);
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
	int gamestate = 0;
	int map1[x][y];
	if (!load_map("MAPS\\map1.txt", map1))
		return -1;
	int map2[x][y];
	if (!load_map("MAPS\\map2.txt", map2))
		return -1;
	enemy creatures[5] = {//Infos ennemies lvl 1
		{1,8,'X',1,1},
		{8,2 ,'X',1,1},
		{8,17,'X',1,1},
		{1,1 ,'X',1,1},
		{5,10,'X',1,1}
	};
	enemy creatures2[5] = {// Infos ennemis lvl2 
		{2,8,'X',1,1},
		{8,3 ,'X',1,1},
		{8,18,'X',1,1},
		{1,8 ,'X',1,1},
		{3,10,'X',1,1}
	};
	entity player{ 2,4,'H',1 }; //Infos Joueur lvl 1
	entity player2{ 2,2,'H',2 }; //Infos Joueur lvl 2
	char input = 'p';
	storytime(input, gamestate); //Ecran de lancement + Lore 
	while (gamestate != 666)//boucle du jeu
	{
		gamestate = level_playing(map1, creatures, player, input);
		if (gamestate == 1)
		{
			gamestate = level_playing(map2, creatures2, player2, input);
		}
		system("cls");
		std::cout << "you win";
		return -1;
	}
	system("cls");
	storytime(input, gamestate);
	return 666;
}