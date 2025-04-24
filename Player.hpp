#pragma once
#include "libraries.hpp"
#include "Battleship.hpp"

class Player {
public:
    virtual void takeTurn(Battleship& game, int row, int col, bool& gameOver, sf::Text& winnerText) = 0;
    virtual ~Player() = default;
};

class HumanPlayer1 : public Player {
public:
    void takeTurn(Battleship& game, int row, int col, bool& gameOver, sf::Text& winnerText) override {
        if (game.checkShot(game.computerBoard, game.playerStats, row, col)) {
            game.outputCurrentMove(row, col, true, "Player 1");
            if (game.isWinner(game.playerStats)) {
                winnerText.setString("Player 1 Wins!");
                gameOver = true;
            }
        } else {
            game.outputCurrentMove(row, col, false, "Player 1");
        }
    }
};

class HumanPlayer2 : public Player {
public:
    void takeTurn(Battleship& game, int row, int col, bool& gameOver, sf::Text& winnerText) override {
        if (game.checkShot(game.playerBoard, game.computerStats, row, col)) {
            game.outputCurrentMove(row, col, true, "Player 2");
            if (game.isWinner(game.computerStats)) {
                winnerText.setString("Player 2 Wins!");
                gameOver = true;
            }
        } else {
            game.outputCurrentMove(row, col, false, "Player 2");
        }
    }
};
