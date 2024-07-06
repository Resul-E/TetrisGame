#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "headers/grid.hpp"
#include "headers/shapes.hpp"
#include "headers/game.hpp"

double lastUpdateTime = 0;

sf::Clock gameTime;

bool EventTriggered(double interval)
{
    double currTime = gameTime.getElapsedTime().asMilliseconds();
    if(currTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currTime;
        return true;
    }
    return false;
}



int main()
{


    sf::RenderWindow window(sf::VideoMode(700, 700), "Tetris");
    window.setFramerateLimit(60);

    Game game = Game();


    while (window.isOpen())
    {

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed)
            {
                sf::Keyboard::Key key = event.key.code;
                game.handleInput(key, window);
            }


        }
        
        if(EventTriggered(game.gameSpeed - ((game.score / 500) * 50)))
        {
                game.MoveShapeDown();
        }
        
        // if(game.score > 0 && game.score > game.grid.shrinkWantedScore)
        // {
        //     game.grid.ShrinkBoard();
        // }

        window.clear(sf::Color(44, 62, 80));

        game.Draw(window);
    
        
        window.display();
    }

    return 0;
}