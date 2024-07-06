#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>


class Grid
{
public:
    Grid();
    void initSounds();
    int gridMatrix[20][10];
    void initGridMatrix();
    void printGridMatrix();
    void Draw(sf::RenderWindow& window);
    void DrawInGame(sf::RenderWindow& window);
    void DrawGameOver(sf::RenderWindow& window);
    int isCellEmpty(int row, int col);
    int ClearFullRows();
    int rowsCleared;
    int theme = 1;
    int shrink = 0;
    void ShrinkBoard();
    sf::Vector2f shrinkDim = {300,0};
    sf::RectangleShape ShrinkRect;
    void InitShrink();
    int shrinkWantedScore = 200;

private:
    bool isRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int num);
    int numRows;
    int numCols;
    int cellSize;
    std::vector<sf::Color> getCellColors();
    std::vector<sf::Color> colors;
    sf::Sound rowClearSound;
    sf::SoundBuffer buffer;
    

    friend class Shape;
    friend class Game;
};