#include "headers/grid.hpp"



Grid::Grid()
{
    initSounds();
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    initGridMatrix();
    colors = getCellColors();
}

void Grid::initSounds()
{
    buffer.loadFromFile("source/audio/clearrow.wav");
    rowClearSound.setBuffer(buffer);
}

void Grid::initGridMatrix()
{
    for(int row = 0; row < numRows; row++)
    {
        for(int col = 0; col < numCols; col++)
        {
            gridMatrix[row][col] = 0;
        }
    }
}

void Grid::printGridMatrix()
{
    for(int row = 0; row < numRows; row++)
    {
        for(int col = 0; col < numCols; col++)
        {
            std::cout << gridMatrix[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::Draw(sf::RenderWindow& window)
{
    for(int row = 0; row < numRows; row++)
    {
        for(int col = 0; col < numCols; col++)
        {
            int cellColorVal = gridMatrix[row][col];
            sf::RectangleShape cell;
            cell.setSize(sf::Vector2f(cellSize - 1, cellSize - 1));
            cell.setPosition(col * cellSize + 201, row * cellSize + 11);
            cell.setFillColor(colors[cellColorVal]);
            
            window.draw(cell);   
        }
    }
}

void Grid::DrawInGame(sf::RenderWindow& window)
{
    sf::Font font;
    font.loadFromFile("source/fonts/8bit16.ttf");

    sf::Text scoreboard("SCOREBOARD", font, 20);
    sf::Text hold("HOLD", font, 20);
    sf::Text preview("PREVIEW", font, 20);
    sf::Text UserGuide("Move -> Arrows\n\n\nHold -> 'H'\n\n\nHardfall -> 'space'\n\n\nReset -> 'R'", font, 13);

    scoreboard.setPosition(520, 20);
    hold.setPosition(20, 20);
    preview.setPosition(520, 230);
    UserGuide.setPosition(10, 300);
    
    scoreboard.setFillColor(sf::Color::Black);
    hold.setFillColor(sf::Color::Black);
    preview.setFillColor(sf::Color::Black);
    UserGuide.setFillColor(sf::Color::Black);

    window.draw(scoreboard);
    window.draw(hold);
    window.draw(preview);
    window.draw(UserGuide);


    sf::RectangleShape boardS;
    sf::RectangleShape boardH;
    sf::RectangleShape boardP;
    boardS.setFillColor(sf::Color(52, 73, 94));
    boardS.setSize({150, 50});
    boardS.setPosition(520, 55);
    boardH.setFillColor(sf::Color(52, 73, 94));
    boardH.setSize({150, 150});
    boardH.setPosition(20, 55);
    boardP.setFillColor(sf::Color(52, 73, 94));
    boardP.setSize({150, 150});
    boardP.setPosition(520, 265);

    window.draw(boardS);
    window.draw(boardH);
    window.draw(boardP);
}

void Grid::DrawGameOver(sf::RenderWindow& window)
{
    sf::Font font;
    font.loadFromFile("source/fonts/8bit16.ttf");

    sf::Text gameover("GAME OVER", font, 20);
    sf::Text restart("Press Enter To Restart", font , 20);

    gameover.setPosition(290, 620);
    restart.setPosition(190, 650);
    
    gameover.setFillColor(sf::Color::Red);
    restart.setFillColor(sf::Color::Red);


    window.draw(gameover);
    window.draw(restart);
}

int Grid::isCellEmpty(int row, int col)
{
    if(gridMatrix[row][col] == 0)
    {
        return 1;
    }else if(gridMatrix[row][col] == 19)
    {
        return 2;
    }
    return 0;
}

int Grid::ClearFullRows()
{
    int completed = 0;

    for(int row = numRows - 1; row >= 0; row--)
    {
        if(isRowFull(row))
        {
            ClearRow(row);
            rowClearSound.play();
            completed++;
        }else if(completed > 0)
        {
            MoveRowDown(row, completed);
        }
    }
    return completed;
}

bool Grid::isRowFull(int row)
{
    for(int col = 0; col < numCols; col++)
    {
        if(gridMatrix[row][col] == 0 || gridMatrix[row][col] == 19)
        {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row)
{
    for(int col = 0; col < numCols; col++)
    {
        gridMatrix[row][col] = 0;
    }
}

void Grid::MoveRowDown(int row, int num)
{
    for(int col = 0; col < numCols; col++)
    {
        gridMatrix[row + num][col] = gridMatrix[row][col];
        gridMatrix[row][col] = 0;
    }



}

std::vector<sf::Color> Grid::getCellColors()
{

    sf::Color gray = {200, 200, 200};
    sf::Color cyan = {0, 255, 255};
    sf::Color yellow = {241, 196, 15};
    sf::Color purple = {155, 89, 182};
    sf::Color green = {46, 204, 113};
    sf::Color red = {231, 76, 60};
    sf::Color blue = {52, 152, 219};
    sf::Color orange = {230, 126, 34};
    sf::Color pink = {255, 102, 178};
    sf::Color turquoise = {64, 224, 208};
    sf::Color brown = {139, 69, 19};


    return {gray, cyan, yellow, purple, green, red, blue, orange, pink, turquoise, brown};
}

void Grid::ShrinkBoard()
{
    shrinkWantedScore += 200;
    shrink++;
    int rowIndex = 20 - shrink;

    for(int i = 0; i < 10; i++)
    {
        gridMatrix[rowIndex][i] = 19;
    }
    shrinkDim.y += 30;
    InitShrink();
}

void Grid::InitShrink()
{
    ShrinkRect.setSize(shrinkDim);
    ShrinkRect.setPosition(200, 610 - shrinkDim.y);
    ShrinkRect.setFillColor(sf::Color::Red);
}