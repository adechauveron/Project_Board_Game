#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <conio.h>

static const int x = 10;
static const int y = 20;
static const int NB_ENEMIES = 5;
static const char directions[4] = { 'z', 's', 'q', 'd' };
static const int SPELL_RANGE = 1;  // portée du sort : 1 bloc autour du joueur
static const int SPELL_DAMAGE = 1; // dégâts infligés par le sort

struct cursor // Curseur du sort
{
	int coord_x;
	int coord_y;
	char name;
};
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

enum class PlayerMode
{
	MOVE,  // on déplace le personnage
	SPELL  // on déplace le curseur du sort
};

const tile water{ '~',1,false }; //Infos Tile Water
const tile mountain{ 'M',2, false };//Infos Tile Mountain
const tile ground{ '.',0, true,false };//Infos Tile Ground
const tile win{ 'E',3,true,true }; // Infos Tile Win
tile const tiles[4] = { ground, water, mountain, win }; //Tableau des différents types de Tiles

tile get_tile_at(int map[x][y], int coord_x, int coord_y) // Récupérer une tile aux coordonnées x et y
{
	return tiles[map[coord_x][coord_y]];
}

bool win_condition(entity& player, int map[x][y], int coord_x, int coord_y) // vérifie la condition de victoire (atteindre E)
{
	return get_tile_at(map, coord_x, coord_y).win_cond;
}

bool still_alive(const enemy& creature) // Un ennemi est vivant tant qu'il lui reste de la vie
{
	return creature.monster.health > 0;
}

bool collidingenemy(enemy creatures[NB_ENEMIES], int coord_x, int coord_y) //Renvoie Vrai si un ennemi se trouve aux coordonnées x et y
{
	for (int current_m = 0; current_m < NB_ENEMIES; current_m++)
	{
		if (still_alive(creatures[current_m]) && coord_x == creatures[current_m].monster.coord_x && coord_y == creatures[current_m].monster.coord_y)
		{
			return true;
		}
	}
	return false;
}

void losinghealth(entity& player, enemy creatures[NB_ENEMIES]) //Calcule les dégats après avoir touché un ennemi
{
	for (int current_m = 0; current_m < NB_ENEMIES; current_m++)
	{
		if (collidingenemy(creatures, player.coord_x, player.coord_y))
		{
			if (still_alive(creatures[current_m])&& player.coord_x == creatures[current_m].monster.coord_x && player.coord_y == creatures[current_m].monster.coord_y)
			{
				player.health -= creatures[current_m].damage;
			}
		}
	}
}

void afficherMap(int map[x][y], entity player, enemy creatures[NB_ENEMIES]) // Affiche le plateau
{
	for (int i = 0; i < x; i++) //i = ligne
	{
		for (int j = 0; j < y; j++) //j = colonne
		{
			int enemyexist = -1;
			for (int current_m = 0; current_m < NB_ENEMIES; current_m++)
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
// Déplacement UNIQUE pour le joueur ET les ennemis.
// dir : 'z' haut, 's' bas, 'q' gauche, 'd' droite (toute autre touche = pas de mouvement)
// creatures : si non nul, la case visée doit être libre de tout ennemi (utile pour les ennemis)
void move_entity(entity& entity, char direction, int map[x][y], enemy* creatures = nullptr)
{
	int dx = 0;
	int dy = 0;

	switch (direction)
	{
	case 'z': dx = -1; break;
	case 's': dx = 1;  break;
	case 'q': dy = -1; break;
	case 'd': dy = 1;  break;
	default:  return;
	}

	int next_x = entity.coord_x + dx;
	int next_y = entity.coord_y + dy;

	if (next_x < 0 || next_x >= x || next_y < 0 || next_y >= y) // hors du plateau
		return;
	if (!get_tile_at(map, next_x, next_y).traversal) // tile non traversable
		return;
	if (creatures != nullptr && collidingenemy(creatures, next_x, next_y)) // case déjà occupée par un ennemi
		return;

	entity.coord_x = next_x;
	entity.coord_y = next_y;
}

void creaturesM(enemy creatures[NB_ENEMIES], int map[x][y])//Deplacement ennemis (aléatoire)
{
	for (int current_m = 0; current_m < NB_ENEMIES; current_m++)
	{
		move_entity(creatures[current_m].monster, directions[rand() % 4], map, creatures);
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

int level_playing(int map[x][y], enemy* creatures, entity player) //Lance le level
{
	while (win_condition(player, map, player.coord_x, player.coord_y) == false)
	{
		afficherMap(map, player, creatures);
		char input = _getch();
		move_entity(player, input, map);
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
	enemy creatures[NB_ENEMIES] = {//Infos ennemies lvl 1
		{1,8,'X',1,1},
		{8,2 ,'X',1,1},
		{8,17,'X',1,1},
		{1,1 ,'X',1,1},
		{5,10,'X',1,1}
	};
	enemy creatures2[NB_ENEMIES] = {// Infos ennemis lvl2 
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
		gamestate = level_playing(map1, creatures, player);

		switch (gamestate)
		{
		case 1: // niveau 1 réussi -> niveau 2
			gamestate = level_playing(map2, creatures2, player2);
			if (gamestate == 1) // niveau 2 réussi -> victoire
			{
				system("cls");
				std::cout << "you win";
				return 9;
			}
			break;
		default: // 666 : le joueur est mort, la boucle s'arrête
			break;
		}
	}
	system("cls");
	storytime('p', gamestate);
	return 666;
}