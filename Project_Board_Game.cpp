#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <conio.h>

static const int x = 10;
static const int y = 20;
static const int nb_enemies = 5;

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

struct level
{
	std::string map_file;
	entity player;
	enemy creatures[nb_enemies];
};

const tile water{ '~',1,false }; //Infos Tile Water
const tile mountain{ 'M',2, false };//Infos Tile Mountain
const tile ground{ '.',0, true,false };//Infos Tile Ground
const tile win{ 'E',3,true,true }; // Infos Tile Win
tile const tiles[4] = { ground, water, mountain, win }; //Tableau des différents types de Tiles
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
	},
	{	
		"MAPS\\map3.txt",//Niveau 3
		{0,0,'H',1},//joueur3
	{
		{3,9,'X',1,1},//créatures niveau3
		{9,3,'X',1,1},
		{5,10,'X',1,1},
		{7,8,'X',1,1},
		{2,18,'X',1,1}}
	}
};
const int nb_levels = sizeof(levels) / sizeof(levels[0]);

tile get_tile_at(int map[x][y], int coord_x, int coord_y) // Récupérer une tile aux coordonnées x et y
{
	return tiles[map[coord_x][coord_y]];
}

bool win_condition(int map[x][y], int coord_x, int coord_y) // vérifie la condition de victoire (atteindre E)
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
	{
		if (still_alive(creatures[current_m]) && coord_x == creatures[current_m].monster.coord_x && coord_y == creatures[current_m].monster.coord_y)
		{
			return true;
		}
	}
	return false;
}

void losinghealth(entity& player, enemy creatures[nb_enemies]) //Calcule les dégats après avoir touché un ennemi
{
	for (int current_m = 0; current_m < nb_enemies; current_m++)
	{
		if (collidingenemy(creatures, player.coord_x, player.coord_y))
		{
			if (still_alive(creatures[current_m]) && player.coord_x == creatures[current_m].monster.coord_x && player.coord_y == creatures[current_m].monster.coord_y)
			{
				player.health -= creatures[current_m].damage;
			}
		}
	}
}

void showMap(int map[x][y],entity player, enemy creatures[nb_enemies]) // Affiche le plateau
{
	for (int i = 0; i < x; i++) //i = ligne
	{
		for (int j = 0; j < y; j++) //j = colonne
		{
			int enemyexist = -1;
			for (int current_m = 0; current_m < nb_enemies; current_m++)
			{
				if (i == creatures[current_m].monster.coord_x && j == creatures[current_m].monster.coord_y)
				{
					enemyexist = current_m;
				}
			}

			if (enemyexist != -1) //Place les monstres
			{
				std::cout << creatures[enemyexist].monster.name << ' ';
			}
			else if (i == player.coord_x && j == player.coord_y)
			{
				std::cout << player.name << ' '; //Place l'Avatar
			}
			else
			{
				std::cout << tiles[map[i][j]].name << ' '; //Place les tiles
			}
		}
		std::cout << std::endl;
	}
}

void move_entity(entity& entity, char direction, int map[x][y], enemy* creatures = nullptr)
{
	int directionx = 0;
	int directiony = 0;

	switch (direction)
	{
		case 'z':
		{
			directionx = -1;
			break;
		}
		case 's':
		{
			directionx = 1;
			break;
		}
		case 'q':
		{
			directiony = -1;
			break;
		}
		case 'd':
		{
			directiony = 1;
			break;
		}
		default:
		{ 
			return; 
		}
	}
	int movement_x = entity.coord_x + directionx;
	int movement_y = entity.coord_y + directiony;

	if (movement_x < 0 || movement_x >= x || movement_y < 0 || movement_y >= y) // hors du plateau
	{
		return;
	}
	if (!get_tile_at(map, movement_x, movement_y).traversal) // tile non traversable
	{
		return;
	}
	if (creatures != nullptr && collidingenemy(creatures, movement_x, movement_y)) // case déjà occupée par un ennemi
	{
		return;
	}

	entity.coord_x = movement_x;
	entity.coord_y = movement_y;
}

void creaturesMove(enemy creatures[nb_enemies], int map[x][y])//Deplacement ennemis (aléatoire)
{
	static const char directions[4] = { 'z', 's', 'q', 'd' };
	for (int current_m = 0; current_m < nb_enemies; current_m++)
	{
		move_entity(creatures[current_m].monster, directions[rand() % 4], map, creatures); //utilse move_entity en revoyant un char au hasard
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
	std::ifstream file(maps); //lit le fichier
	if (!file) //La fonction n'arrive pas à lire le fichier texte
	{
		std::cout << "Impossible d'ouvrir " << maps << std::endl;
		return false;
	}

	std::string line; //Initie la ligne de texte
	for (int i = 0; i < x; i++)
	{
		if (!std::getline(file, line) || line.size() < y) //verifie s'il peut pas atteindre la ligne et si la taille de la ligne est correcte
		{
			std::cout << "Ligne " << i << " invalide ou trop courte" << std::endl;
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
					<< "' ligne " << i << ", colonne " << j << std::endl;
				return false;
			}
			map[i][j] = value;
		}
	}
	return true;
}



int level_playing(int map[x][y], enemy* creatures, entity player,Item item) //Lance le level
{
	while (win_condition( map, player.coord_x, player.coord_y) == false) //Tant que la case Win n'est pas atteinte la boucle de jeu continue !
	{
		showMap(map, player, creatures);
		char input = _getch();
		move_entity(player, input, map);
		losinghealth(player, creatures);
		creaturesMove(creatures, map);
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

	char input = 'p';//Initie l'input qui va lancer le storytime
	storytime(input, 0); //Ecran de lancement + Lore 
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

		int gamestate = level_playing(map, creatures, levels[current_level].player,Swimming_Getup);

		if (gamestate == 666) // le joueur est mort -> Game Over
		{
			system("cls");
			storytime('p', gamestate);
			return 666;
		}

	}
}