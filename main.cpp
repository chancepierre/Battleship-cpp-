#include <SFML/Graphics.hpp>
#include "Battleship.h"

int main()
{
    Battleship game;

    sf::RenderWindow window(sf::VideoMode(600, 600), "Battleship Game");
    window.setFramerateLimit(60);

    game.play();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        sf::RectangleShape cell(sf::Vector2f(50, 50));
        cell.setOutlineThickness(1);
        cell.setOutlineColor(sf::Color::White);
        cell.setFillColor(sf::Color::Transparent);

        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                cell.setPosition(i * 50.f, j * 50.f);
                window.draw(cell);
            }
        }

        window.display();
    }

    return 0;
}

