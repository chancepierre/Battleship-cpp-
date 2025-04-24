#include "Player.hpp"
#include "Battleship.hpp"

void HumanPlayer1::takeTurn(Battleship& game, int row, int col, bool& gameOver, sf::Text& winnerText) {
    bool hit = game.checkShot(game.computerBoard, game.playerStats, row, col);
    game.outputCurrentMove(row, col, hit, "Player 1");
    if (hit && game.isWinner(game.playerStats)) {
        winnerText.setString("Player 1 Wins!");
        gameOver = true;
    }
}

void HumanPlayer2::takeTurn(Battleship& game, int row, int col, bool& gameOver, sf::Text& winnerText) {
    bool hit = game.checkShot(game.playerBoard, game.computerStats, row, col);
    game.outputCurrentMove(row, col, hit, "Player 2");
    if (hit && game.isWinner(game.computerStats)) {
        winnerText.setString("Player 2 Wins!");
        gameOver = true;
    }
}
