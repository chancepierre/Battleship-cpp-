#pragma once
#include "libraries.hpp"

//base class for various types of ships
class Ship
{
public:
	Ship(string ship_name, int ship_size);
	virtual ~Ship() {}

	virtual void placeShip(int x_start, int y_start, bool horizontal);
	virtual bool isSunk()const;
	virtual bool isHit(int x, int y);

	int	getSize()const;
	std::string getName()const;
	vector<pair<int, int>> getCoordinates()const;

protected:
	string name;
	int size;
	int hits;
	vector<pair<int, int>> coordinates;

};
