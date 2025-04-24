#include <SFML/Graphics.hpp>
#include "Battleship.hpp"
#include "Player.hpp"
#include "testFunctions.hpp"

const int CELL_SIZE = 50;

int main()
{
    //test functions
    testHitDetection();
    testMissDetection();
    testDoubleShotPrevention();
    testWinDetection();
    testGameRestart();

   
    Battleship game;
    bool showMenu = true;
    bool playerTurn = true;
    bool gameOver = false;

    HumanPlayer1 p1;
    HumanPlayer2 p2;

    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * BOARD_SIZE, CELL_SIZE * BOARD_SIZE + 100), "Battleship - Player vs Player");
    window.setFramerateLimit(60);

    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    cell.setOutlineThickness(1);
    cell.setOutlineColor(sf::Color::White);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        return -1;

    sf::Text playerTurnText;
    playerTurnText.setFont(font);
    playerTurnText.setCharacterSize(24);
    playerTurnText.setFillColor(sf::Color::White);
    playerTurnText.setPosition(10, CELL_SIZE * BOARD_SIZE + 10);

    sf::Text winnerText;
    winnerText.setFont(font);
    winnerText.setCharacterSize(32);
    winnerText.setFillColor(sf::Color::Green);
    winnerText.setPosition(50, 50);

    sf::Text restartText;
    restartText.setFont(font);
    restartText.setCharacterSize(20);
    restartText.setFillColor(sf::Color::Yellow);
    restartText.setString("Click to restart");
    restartText.setPosition(50, 100);

    sf::Text label;
    label.setFont(font);
    label.setCharacterSize(16);
    label.setFillColor(sf::Color::White);

    sf::Text menuText;
    menuText.setFont(font);
    menuText.setCharacterSize(16);
    menuText.setFillColor(sf::Color::Cyan);
    menuText.setPosition(20, 50);
    menuText.setString(
        "WELCOME TO BATTLESHIP\n\n"
        "How to Play:\n"
        "- Click on the grid to fire shots at your opponent\n"
        "- Red squares are hits, grey squares are misses\n"
        "- Sink all enemy ships to win!\n\n"
        "Player 1 and Player 2 take turns.\n"
        "Turns switch automatically after each shot.\n"
        "\nClick anywhere to start...");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (showMenu)
                {
                    showMenu = false;
                    game = Battleship();
                    game.randomlyPlaceShips(game.playerBoard);
                    game.randomlyPlaceShips(game.computerBoard);
                    gameOver = false;
                    playerTurn = true;
                    continue;
                }

                if (gameOver)
                {
                    game = Battleship();
                    game.randomlyPlaceShips(game.playerBoard);
                    game.randomlyPlaceShips(game.computerBoard);
                    gameOver = false;
                    playerTurn = true;
                    continue;
                }

                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int row = mousePos.y / CELL_SIZE;
                int col = mousePos.x / CELL_SIZE;

                if (row < BOARD_SIZE && col < BOARD_SIZE)
                {
                    if (playerTurn)
                        p1.takeTurn(game, row, col, gameOver, winnerText);
                    else
                        p2.takeTurn(game, row, col, gameOver, winnerText);

                    playerTurn = !playerTurn;
                }
            }
        }

        window.clear(sf::Color::Black);

        if (showMenu)
        {
            window.draw(menuText);
            window.display();
            continue;
        }

        if (!gameOver)
            playerTurnText.setString(playerTurn ? "Player 1's Turn" : "Player 2's Turn");

        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                cell.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                char val = playerTurn ? game.computerBoard[i][j] : game.playerBoard[i][j];

                if (val == '*')
                    cell.setFillColor(sf::Color::Red);
                else if (val == 'm')
                    cell.setFillColor(sf::Color(128, 128, 128));
                else
                    cell.setFillColor(sf::Color::Blue);

                window.draw(cell);
            }
        }

        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            label.setString(std::to_string(j));
            label.setPosition(j * CELL_SIZE + CELL_SIZE / 2 - 5, 0);
            window.draw(label);
        }

        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            label.setString(std::to_string(i));
            label.setPosition(0, i * CELL_SIZE + CELL_SIZE / 2 - 10);
            window.draw(label);
        }

        window.draw(playerTurnText);

        if (gameOver)
        {
            window.draw(winnerText);
            window.draw(restartText);
        }

        window.display();
    }

    game.outputStats("Player 1", game.playerStats);
    game.outputStats("Player 2", game.computerStats);

    return 0;
}
