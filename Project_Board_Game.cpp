#include <iostream>
#include <string>


static const int x = 10;
static const int y = 20;

struct entity {
	int c_x;
	int c_y;
	int health;
	char name;
};

struct tile {
	char name;
	bool traversal;
};

/*
. — Basic ground
~ — Water
A — Mountain
H - heros
	*/
entity player{ 2, 4 , 1, 'H' };
const tile water{ '~',false};
const tile mountain{ 'A', false};
const tile ground{ '.', true};

void afficherMap(int map[10][20], entity player)
{
	for (int i = 0; i < x; i++) //i = ligne
	{
		for (int j = 0; j < y; j++) //j = colonne
		{
			if (i == player.c_x && j == player.c_y)
			{
				std::cout << player.name << ' ';
			}
			else if (map[i][j] == 1) {
				std::cout << water.name << ' ';
			}
			else if (map[i][j] == 2) {
				std::cout << mountain.name << ' ';
			}
			else {
				std::cout << ground.name << ' ';
			}
		}
		std::cout <<std::endl;
	}
}

void player_choice(entity &player,char input, int map[10][20])
{
	
}

int main()
{
	int map1[10][20] = 
{ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
char input;
std::cin >> input;
afficherMap(map1,player);
return 0;
}
