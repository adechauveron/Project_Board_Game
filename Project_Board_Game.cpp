#include <iostream>
#include <cstdlib>
#include <ctime>

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
};
const tile water{ '~',1,false }; //Infos Tile Water
const tile mountain{ 'M',2, false };//Infos Tile Mountain
const tile ground{ '.',0, true };//Infos Tile Ground
tile const tiles[3] = { ground, water, mountain }; //Tableau des différents types de Tiles

tile get_tile_at(int map[10][20], int x, int y)
{
	int index = map[x][y];
	tile current_tile = tiles[index];
	return current_tile;
}

bool collidingenemy(enemy creatures[5], int x, int y)
{
	for (int current_m = 0; current_m < 5; current_m++)
	{
		if (x == creatures[current_m].monster.coord_x && y == creatures[current_m].monster.coord_y)
		{
			std::cout << "ENNEMI";
			return true;
		}

	}
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
				if (i == creatures[current_m].monster.coord_x && j == creatures[current_m].monster.coord_y)
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
				for (int c = 0; c < 3; c++)
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
				if (collidingenemy(creatures, creatures[current_m].monster.coord_x - 1, creatures[current_m].monster.coord_y))
				{
					block += 1;
				}
				else {
					creatures[current_m].monster.coord_x -= 1;
				}
				
			}
		}
		else if (random == 1 && creatures[current_m].monster.coord_x < 9)
		{
			tile Next_tile = get_tile_at(map, creatures[current_m].monster.coord_x + 1, creatures[current_m].monster.coord_y);
			if (Next_tile.traversal)
			{
				if (collidingenemy(creatures, creatures[current_m].monster.coord_x - 1, creatures[current_m].monster.coord_y))
				{
					block += 1;

				}
				else
				{
					creatures[current_m].monster.coord_x += 1;
				}
				
			}
		}
		else if (random == 2 && creatures[current_m].monster.coord_y > 0)
		{
			tile Next_tile = get_tile_at(map, creatures[current_m].monster.coord_x, creatures[current_m].monster.coord_y - 1);
			if (Next_tile.traversal)
			{
				if (collidingenemy(creatures, creatures[current_m].monster.coord_x, creatures[current_m].monster.coord_y - 1))
				{
					block += 1;
				}
				else
				{
					creatures[current_m].monster.coord_y -= 1;
				}
			}
		}
		else if (random == 0 && creatures[current_m].monster.coord_y < 19)
		{
			tile Next_tile = get_tile_at(map, creatures[current_m].monster.coord_x, creatures[current_m].monster.coord_y + 1);
			if (Next_tile.traversal)
			{
				if (collidingenemy(creatures, creatures[current_m].monster.coord_x, creatures[current_m].monster.coord_y + 1))
				{
					block += 1;
				}
				else
				{
					creatures[current_m].monster.coord_y += 1;
				}

			}
		}
		std::cout << block;
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
	{1,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};
	enemy creatures[5] = {
		{1,8,'X',1,1},
		{8,2 ,'X',1,1},
		{8,17,'X',1,1},
		{1,1 ,'X',1,1},
		{5,10,'X',1,1}
	}; //Infos ennemies
	entity player{ 2,4,'H',1 }; //Infos Joueur
	char input;
	while (player.health != 0)//boucle du jeu
	{
		afficherMap(map1, player, creatures);
		std::cout << "Ordonner votre avatar : ";
		std::cin >> input;
		player_choice(player, input, map1);
		losinghealth(player, creatures);
		creaturesM(creatures, map1);
		losinghealth(player, creatures);
		if (player.health <= 0)
		{
			system("cls");
			std::cout << "GAME OVER" << '\n' << "Vous avez perdu la partie !" << '\n';
			return 1;
		}
	}
	return 0;
}
