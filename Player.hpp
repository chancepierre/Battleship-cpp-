#pragma once
#include <SFML/Graphics.hpp>

class Battleship; // Forward declaration

class Player {
public:
    virtual void takeTurn(Battleship& game, int row, int col, bool& gameOver, sf::Text& winnerText) = 0;
    virtual ~Player() = default;
};

class HumanPlayer1 : public Player {
public:
    void takeTurn(Battleship& game, int row, int col, bool& gameOver, sf::Text& winnerText) override;
};

class HumanPlayer2 : public Player {
public:
    void takeTurn(Battleship& game, int row, int col, bool& gameOver, sf::Text& winnerText) override;
};
