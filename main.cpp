#include <SFML/Graphics.hpp>
#include "Battleship.h"

const int CELL_SIZE = 50;

int main()
{
    Battleship game;

    // Randomly place ships for both players
    game.randomlyPlaceShips(game.playerOneBoard);  // Player 1
    game.randomlyPlaceShips(game.playerTwoBoard);  // Player 2
    std::cout << "Ships placed randomly for both players.\n";

    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * BOARD_SIZE, CELL_SIZE * BOARD_SIZE), "Battleship - Player vs Player");
    window.setFramerateLimit(60);

    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    cell.setOutlineThickness(1);
    cell.setOutlineColor(sf::Color::White);

    bool playerOneTurn = true;
    bool gameOver = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && !gameOver)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int row = mousePos.y / CELL_SIZE;
                int col = mousePos.x / CELL_SIZE;

                if (row < BOARD_SIZE && col < BOARD_SIZE)
                {
                    bool hit;
                    if (playerOneTurn)
                    {
                        hit = game.checkShot(game.playerTwoBoard, game.playerOneStats, row, col);
                        game.outputCurrentMove(row, col, hit, "Player 1");

                        if (game.isWinner(game.playerOneStats)) {
                            std::cout << "Player 1 wins!" << std::endl;
                            gameOver = true;
                        }
                    }
                    else
                    {
                        hit = game.checkShot(game.playerOneBoard, game.playerTwoStats, row, col);
                        game.outputCurrentMove(row, col, hit, "Player 2");

                        if (game.isWinner(game.playerTwoStats)) {
                            std::cout << "Player 2 wins!" << std::endl;
                            gameOver = true;
                        }
                    }

                    playerOneTurn = !playerOneTurn;
                }
            }
        }

        window.clear(sf::Color::Black);

        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                cell.setPosition(j * CELL_SIZE, i * CELL_SIZE);

                // Show the current player's target board
                char val = playerOneTurn ? game.playerTwoBoard[i][j] : game.playerOneBoard[i][j];

                if (val == '*')
                    cell.setFillColor(sf::Color::Red);
                else if (val == 'm')
                    cell.setFillColor(sf::Color(128, 128, 128));
                else
                    cell.setFillColor(sf::Color::Blue);

                window.draw(cell);
            }
        }

        window.display();
    }

    game.outputStats("Player 1", game.playerOneStats);
    game.outputStats("Player 2", game.playerTwoStats);

    return 0;
}
