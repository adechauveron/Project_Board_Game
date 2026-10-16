#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

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
	int current_x;
	int current_y;
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
const tile win{'E',3,true,true};
tile const tiles[4] = { ground, water, mountain, win}; //Tableau des différents types de Tiles

tile get_tile_at(int map[10][20], int x, int y)
{
	int index = map[x][y];
	tile current_tile = tiles[index];
	return current_tile;
}

bool win_condition(entity& player, int map[10][20], int x, int y)
{
	tile win = get_tile_at(map, x, y);
	if (win.win_cond == true)
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

void losinghealth(entity& player, enemy creatures[5])
{
	for (int current_m = 0; current_m < 5; current_m++)
	{
		if (collidingenemy(creatures, player.coord_x, player.coord_y) == true)
		{
			player.health -= creatures[current_m].damage;
		}
	}
}

void afficherMap(int map[10][20], entity player, enemy creatures[5]) // Affiche le plateau
{
	for (int i = 0; i < x; i++) //i = ligne
	{
		for (int j = 0; j < y; j++) //j = colonne
		{
			bool spawnenemy = false;
			int enemyexist;

			for (int current_m = 0; current_m < 5; current_m++) //Place les monstres
			{
				if (i == creatures[current_m].current_x && j == creatures[current_m].current_y)
				{
					spawnenemy = true;
					enemyexist = current_m;
				}
			}
			if (spawnenemy)
			{
				std::cout << creatures[enemyexist].monster.name << ' ';
			}
			else if (i == player.coord_x && j == player.coord_y) //Place l'Avatar
			{
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
			}
		}
		std::cout << std::endl;
	}
}

void player_choice(entity& player, char choice, int map[10][20])//Prend les Input du Joueur
{
	if (choice == 'z' && player.coord_x > 0)
	{
		tile Next_tile = get_tile_at(map, player.coord_x - 1, player.coord_y);
		if (Next_tile.traversal)
		{
			player.coord_x -= 1;
		}
	}
	else if (choice == 's' && player.coord_x < 9)
	{
		{
			tile Next_tile = get_tile_at(map, player.coord_x + 1, player.coord_y);
			if (Next_tile.traversal)
			{
				player.coord_x += 1;
			}
		}
	}
	else if (choice == 'q' && player.coord_y > 0)
	{
		tile Next_tile = get_tile_at(map, player.coord_x, player.coord_y - 1);
		if (Next_tile.traversal)
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

int main()
{
	srand(time(0));
	int map1[10][20] = //Premier niveau du jeu
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
	while (player.health != 0)//boucle du jeu
	{
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
	return 0;
}

