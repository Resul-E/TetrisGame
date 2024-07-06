#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "grid.hpp"
#include <iostream>

enum shapeEnum
{
    plusSign,
    smallSquare,
    cornerPiece,
    tallTower,
    zigzag,
    uShape,
    stepShape,
    arrowUp,
    doubleZigzag,
    pyramid,
    
};



class Shape
{
private:
    sf::Vector2i position;
    std::vector<std::vector<int>> shapeMatrix;
    sf::Color color;
    int cellSize;

friend class Game;

public:
    shapeEnum name;
    int holdCounter = 2;
    int rotateCounter = 5;
    Shape();
    Shape(shapeEnum shapeName);
    void Draw(sf::RenderWindow& window);
    void Move(int x, int y);

};


