#include <string>
#include <vector>

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

// --- Constantes (const => visibles sans conflit dans chaque .cpp qui inclut ce header) ---
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
	{ "MAPS\\map9.txt", 3 }
};
const int nb_levels = 10;
