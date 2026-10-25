#include <cstdlib>
#include "spell.h"
#include "map.h"

bool in_spell_range(const entity& player, int x, int y)
{
	return (std::abs(x - player.coord_x) <= spell_range && std::abs(y - player.coord_y) <= spell_range);
}

void move_cursor(spell_overlay& spell, char direction, const grid& map, const entity& player)
{
	int new_x = spell.cursor_x;
	int new_y = spell.cursor_y;

	switch (direction)
	{
	case 'z':
		new_x -= 1;
		break;
	case 's':
		new_x += 1;
		break;
	case 'q':
		new_y -= 1;
		break;
	case 'd':
		new_y += 1;
		break;
	default:
		return;
	}

	bool outside = new_x < 0 || new_x >= map_height(map) || new_y < 0 || new_y >= map_width(map);
	if (outside || !in_spell_range(player, new_x, new_y))
	{
		return;
	}

	spell.cursor_x = new_x;
	spell.cursor_y = new_y;
}

bool cast_spell(std::vector<enemy>& creatures, int target_x, int target_y)
{
	for (std::vector<enemy>::iterator it = creatures.begin(); it != creatures.end(); ++it) //Parcourt le tableau dynamique creatures
	{
		if (it->monster.coord_x == target_x && it->monster.coord_y == target_y)
		{
			creatures.erase(it);
			return true;
		}
	}
	return false;
}
