#include <iostream>
#include <string>


static const int x = 10;
static const int y = 20;

struct entity 
{
	int c_x;
	int c_y;
	char name;
	int health;
};

struct enemy
{
	entity hero;
	int damage;
	bool spawn = true;
};

struct tile 
{
	char name;
	int indice;
	bool traversal;
};
const tile water{ '~',1,false}; //Infos Tile Water
const tile mountain{ 'M',2, false};//Infos Tile Mountain
const tile ground{ '.',0, true};//Infos Tile Ground
tile const tiles[3] = { ground, water, mountain }; //Tableau des différents types de Tiles

void afficherMap(int map[10][20], entity player, enemy creatures[5]) // Affiche le plateau
{
	for (int i = 0; i < x; i++) //i = ligne
	{
		for (int j = 0; j < y; j++) //j = colonne
		{
			bool spawnenemy = false;
			int enemyexist;

			for (int m = 0; m < 5; m++) //Place les monstres
			{
				if (i == creatures[m].hero.c_x && j == creatures[m].hero.c_y)
				{
					spawnenemy = true;
					enemyexist = m;
				}
			}
			if (spawnenemy)
			{
				std::cout << creatures[enemyexist].hero.name << ' ';
			}
			else if (i == player.c_x && j == player.c_y) //Place l'Avatar
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
		std::cout <<std::endl;
	}
}

void player_choice(entity &player,char choice, int map[10][20])//Prend les Input du Joueur

{
	if (choice == 'z' && player.c_x > 0)
		{
			for (int c = 0; c < 3; c++)
			{
				if (map[player.c_x - 1][player.c_y] == tiles[c].indice && tiles[c].traversal == true)
					{
						player.c_x -= 1;
						break;
					}
			}
		}
	else if (choice == 's' && player.c_x < 9)
		{
			for (int c = 0; c < 3; c++)
			{
				if (map[player.c_x + 1][player.c_y] == tiles[c].indice && tiles[c].traversal == true)
					{
						player.c_x += 1;
						break;
					}
			}
		}
	else if (choice == 'q' && player.c_y > 0)
		{
			for (int c = 0; c < 3; c++)
				{
					if (map[player.c_x][player.c_y-1] == tiles[c].indice && tiles[c].traversal == true)
					{
						player.c_y -= 1;
						break;
					}
				}
		}
	else if (choice == 'd' && player.c_y < 19)
		{
			for (int c = 0; c < 3; c++)
			{
				if (map[player.c_x][player.c_y+1] == tiles[c].indice && tiles[c].traversal == true)
					{
						player.c_y += 1;
						break;
					}
			}
		}
}

void losinghealth(entity& player, enemy creatures[5])
{
	for (int m = 0; m < 5; m++)
	{
		if (player.c_x == creatures[m].hero.c_x && player.c_y == creatures[m].hero.c_y)
		{
			player.health -= creatures[m].hero.health;
		}
		
	}
}

int main()
{
	int map1[10][20] = //Premier niveau du jeu
{ 
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};
enemy creatures[5] = { { 1, 8,'X', 1, 1},{8, 2 ,'X',1,1},{ 8, 17,'X', 1, 1},{7, 2 ,'X',1,1},{ 5, 10,'X', 1, 1} }; //Infos ennemies
entity player{ 2, 4 ,'H',1 }; //Infos Joueur
char input;
while (player.health != 0)//boucle du jeu
	{
		afficherMap(map1, player,creatures);
		std::cout << "Ordonner votre avatar : ";
		std::cin >> input;
		player_choice(player,input,map1);
		losinghealth(player, creatures);
		system("cls");
		if (player.health <= 0)
		{
		std::cout << "GAME OVER" << '\n' << "Vous avez perdu la partie !";
		}
	}
	return 0;
}
