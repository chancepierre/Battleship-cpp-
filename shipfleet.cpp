#include "shipfleet.hpp"

Destroyer::Destroyer() : Ship("Destroyer", 2) {}
Submarine::Submarine() : Ship("Submarine", 3) {}
Cruiser::Cruiser() : Ship("Cruiser", 3) {}
BBattleship::BBattleship() : Ship("Battleship", 4) {}
Carrier::Carrier() : Ship("Carrier", 5) {}