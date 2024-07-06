#pragma once
#include <SFML/Audio.hpp>
#include <vector>
#include "grid.hpp"
#include "shapes.hpp"
#include <stdlib.h>
#include <time.h>
#include <random>
#include <iostream>

class Game
{
    public:
        Game();
        void Music();
        void playRotate();
        Shape getRandomShape();
        Grid grid;
        void Draw(sf::RenderWindow& window);
        void handleInput(sf::Keyboard::Key key, sf::RenderWindow& window);
        void MoveShapeRight();
        void MoveShapeLeft();
        void MoveShapeDown();
        void RotateShape();
        void BringShapeInside();
        void LockShape();
        bool ShapeFitsDown();
        bool ShapeFitsLeft();
        bool ShapeFitsRight();
        void Reset();
        void CreatePortal();
        void DrawPortal(sf::RenderWindow& window);
        int score;
        void updateScore(int linesCleared, int movedDown);
        void DrawScore(sf::RenderWindow& window);
        void DrawNextShape(sf::RenderWindow& window);
        void DrawRotationWarning(sf::RenderWindow& window);
        void HoldShape();
        void DrawHold(sf::RenderWindow& window);
        int gameSpeed = 500;
        void HardFall();
        int randomRow;
        int randomCol;

    private:
        sf::Music music;
        sf::Sound rotateSound;
        sf::SoundBuffer buffer;
        bool gameOver;
        std::vector<shapeEnum> shapes;
        Shape currShape;
        Shape nextShape;
        Shape holdShape;
        std::vector<sf::Color> colorLs;
        void initRotate();
        bool isHolding = false;
};