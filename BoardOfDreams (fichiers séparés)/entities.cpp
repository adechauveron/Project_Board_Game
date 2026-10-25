#include <cstdlib>
#include "entities.h"
#include "map.h"

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

bool is_move_key(char c)
{
	return c == 'z' || c == 's' || c == 'q' || c == 'd';
}

void move_entity(entity& entity, char direction, const grid& map, const std::vector<enemy>* creatures)
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

void end_turn(entity& player, std::vector<enemy>& creatures, const grid& map)
{
	take_tile_damage(player, map);
	losinghealth(player, creatures);
	creaturesMove(creatures, map);
	losinghealth(player, creatures);
}
