#pragma once 
#include "ship.hpp"
class Destroyer : public Ship
{
public:
	Destroyer();
};

Destroyer::Destroyer() : Ship("Destroyer",2) {}
//

class Submarine: public Ship
{
public:
	Submarine();
};

Submarine::Submarine() : Ship("Submarine", 3) {}

//	


class Cruiser : public Ship
{
public:
	Cruiser();
};

Cruiser::Cruiser() : Ship("Cruiser", 3) {}

//
class BBattleship : public Ship
{
public:
	BBattleship();
};

BBattleship::BBattleship() : Ship("Battleship", 3) {}

//
class Carrier : public Ship
{
public:
	Carrier();

};

Carrier::Carrier() : Ship("Carrier", 3) {}