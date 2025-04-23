#include <SFML/Graphics.hpp>
#include "Battleship.h"

const int CELL_SIZE = 50;

void displayStats(sf::RenderWindow &window, const Stats &playerStats, const Stats &computerStats, const std::string &winner)
{
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        return;

    sf::Text statsText;
    statsText.setFont(font);
    statsText.setCharacterSize(20);
    statsText.setFillColor(sf::Color::White);
    statsText.setPosition(20, 20);

    std::stringstream ss;
    ss << winner << " Wins!\n\n";
    ss << "Player Stats:\n";
    ss << "Hits: " << playerStats.hits << "\nMisses: " << playerStats.misses << "\nShots: " << playerStats.shots
       << "\nAccuracy: " << (playerStats.shots > 0 ? (100.f * playerStats.hits / playerStats.shots) : 0) << "%\n\n";

    ss << "Computer Stats:\n";
    ss << "Hits: " << computerStats.hits << "\nMisses: " << computerStats.misses << "\nShots: " << computerStats.shots
       << "\nAccuracy: " << (computerStats.shots > 0 ? (100.f * computerStats.hits / computerStats.shots) : 0) << "%\n\n";

    ss << "Press any key to exit.";

    statsText.setString(ss.str());

    window.clear(sf::Color::Black);
    window.draw(statsText);
    window.display();

    sf::Event event;
    bool waiting = true;
    while (waiting && window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
            {
                waiting = false;
                window.close();
            }
        }
    }
}

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

        if (gameOver)
    }

    game.outputStats("Player", game.playerStats);
    game.outputStats("Computer", game.computerStats);
    displayStats(window, game.playerStats, game.computerStats, winner);
    return 0;
}

