#include "headers/shapes.hpp"



Shape::Shape() 
{

}

Shape::Shape(shapeEnum shapeName) {

    name = shapeName;
    position = {3,0};
    Grid tempGrid;
    std::vector<sf::Color> colorLs = tempGrid.getCellColors();
    cellSize = tempGrid.cellSize;

    switch (shapeName)
    {
        case plusSign:
        shapeMatrix =  {{0, 1, 0},
                        {1, 1, 1},
                        {0, 1, 0}};
        color = colorLs[plusSign + 1];
        this->position.x += 3 - shapeMatrix[0].size();
        break;

        case smallSquare:
        shapeMatrix =  {{1, 1},
                        {1, 1}};
        color = colorLs[smallSquare + 1];
        this->position.x += 3 - shapeMatrix[0].size();
        break;

        case cornerPiece:
        shapeMatrix =  {{1, 0},
                        {1, 1}};
        color = colorLs[cornerPiece + 1];
        this->position.x += 3 - shapeMatrix[0].size();
        break;

        case tallTower:
        shapeMatrix =  {{1},
                        {1},
                        {1}};
        color = colorLs[tallTower + 1];
        this->position.x += 3 - shapeMatrix[0].size();
        break;

        case zigzag:
        shapeMatrix =  {{0, 1, 1},
                        {1, 1, 0}};
        color = colorLs[zigzag + 1];
        this->position.x += 3 - shapeMatrix[0].size();
        break;

        case uShape:
        shapeMatrix =  {{1, 0, 1},
                        {1, 1, 1}};
        color = colorLs[uShape + 1];
        this->position.x += 3 - shapeMatrix[0].size();
        break;

        case stepShape:
        shapeMatrix =  {{0, 1},
                        {1, 1},
                        {1, 0}};
        color = colorLs[stepShape + 1];
        this->position.x += 3 - shapeMatrix[0].size();
        break;

        case arrowUp:
        shapeMatrix =  {{0, 1, 0},
                        {1, 1, 1},
                        {1, 0, 1}};
        color = colorLs[arrowUp + 1];
        this->position.x += 3 - shapeMatrix[0].size();
        break;

        case doubleZigzag:
        shapeMatrix =  {{1, 0, 0},
                        {1, 1, 1},
                        {0, 0, 1}};
        color = colorLs[doubleZigzag + 1];
        this->position.x += 3 - shapeMatrix[0].size();
        break;

        case pyramid:
        shapeMatrix =  {{0, 1, 0},
                        {1, 1, 1}};
        color = colorLs[pyramid + 1];
        this->position.x += 3 - shapeMatrix[0].size();
        break;

    default:
        break;
    }
}


void Shape::Draw(sf::RenderWindow& window)
{
    for(int row = 0; row < shapeMatrix.size(); row++)
    {
        for(int col = 0; col < shapeMatrix[0].size(); col++)
        {
            int cellColorVal = shapeMatrix[row][col];
            sf::RectangleShape cell;
            cell.setSize(sf::Vector2f(cellSize - 1, cellSize - 1));
            cell.setPosition((col + position.x) * cellSize + 201, (row + position.y) * cellSize + 11);
            if(cellColorVal != 0)
            {
            cell.setFillColor(this->color);
            }else
            {
                continue;
            }

            window.draw(cell);
        }
    }
    
}

void Shape::Move(int x, int y)
{
    this->position.x += x;
    this->position.y += y;
}