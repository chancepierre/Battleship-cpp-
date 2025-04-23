#include "ship.hpp"


Ship::Ship(string ship_name, int ship_size) : name(ship_name), size(ship_size), hits(0) {}


void Ship::placeShip(int x_start, int y_start, bool horizontal)
{
	coordinates.clear();
	for (int i = 0; i < size; ++i)
	{
		if (horizontal)//horizontal value is true
		{
			coordinates.push_back({ x_start + i, y_start });
		}
		else//means its orientaion is vertical
		{
			coordinates.push_back({ x_start, y_start + i });
		}

	}
}
bool Ship::isSunk()const
{
	return hits >= size;

}
bool Ship::isHit(int x, int y)
{
	for (const auto& coord : coordinates)
	{
		if (coord.first == x && coord.second == y)
		{
			hits++;
			return true;
		}
	}

	return false;
}