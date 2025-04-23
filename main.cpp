#include <SFML/Graphics.hpp>
#include "Battleship.h"

const int CELL_SIZE = 50;

int main()
{
    Battleship game;
    game.randomlyPlaceShips(game.playerBoard);
    game.randomlyPlaceShips(game.computerBoard);

    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * BOARD_SIZE, CELL_SIZE * BOARD_SIZE), "Battleship - SFML");

    window.setFramerateLimit(60);
    
    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    cell.setOutlineThickness(1);
    cell.setOutlineColor(sf::Color::White);

    bool playerTurn = true;
    bool gameOver = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && playerTurn && !gameOver)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int row = mousePos.y / CELL_SIZE;
                int col = mousePos.x / CELL_SIZE;

                if (row < BOARD_SIZE && col < BOARD_SIZE)
                {
                    bool hit = game.checkShot(game.computerBoard, game.playerStats, row, col);
                    game.soundEffects(hit);
                    game.outputCurrentMove(row, col, hit, "Player");

                    if (game.isWinner(game.playerStats))
                    {
                        gameOver = true;
                        std::cout << "Player wins!" << std::endl;
                    }

                    playerTurn = false;
                }
            }
        }

        if (!playerTurn && !gameOver)
        {
            int r, c;
            bool shot_valid = false;

            while (!shot_valid)
            {
                r = rand() % BOARD_SIZE;
                c = rand() % BOARD_SIZE;
                if (game.playerBoard[r][c] != '*' && game.playerBoard[r][c] != 'm')
                    shot_valid = true;
            }

            bool hit = game.checkShot(game.playerBoard, game.computerStats, r, c);
            game.outputCurrentMove(r, c, hit, "Computer");

            if (game.isWinner(game.computerStats))
            {
                gameOver = true;
                std::cout << "Computer wins!" << std::endl;
            }

            playerTurn = true;
        }

        window.clear(sf::Color::Black);

        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                cell.setPosition(j * CELL_SIZE, i * CELL_SIZE);

                if (game.computerBoard[i][j] == '*')
                    cell.setFillColor(sf::Color::Red);
                else if (game.computerBoard[i][j] == 'm')
                    cell.setFillColor(sf::Color(128, 128, 128));
                else
                    cell.setFillColor(sf::Color::Blue);

                window.draw(cell);
            }
        }

        window.display();
    }

    game.outputStats("Player", game.playerStats);
    game.outputStats("Computer", game.computerStats);

    return 0;
}

