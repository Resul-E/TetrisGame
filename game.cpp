#include "headers/game.hpp"

Game::Game()
{
    Music();
    initRotate();
    srand(time(NULL));
    gameOver = false;
    grid = Grid();
    grid.initSounds();
    CreatePortal();

    score = 0;

    colorLs = grid.getCellColors();

    shapes = {plusSign, smallSquare, cornerPiece, tallTower, zigzag, uShape, stepShape, arrowUp, doubleZigzag, pyramid};

    currShape = getRandomShape();
    nextShape = getRandomShape();
}

void Game::Music()
{

    music.openFromFile("source/audio/game.wav");
    music.play();
    music.setLoop(true);
}

void Game::initRotate(){
    buffer.loadFromFile("source/audio/rotate.wav");
    rotateSound.setBuffer(buffer);
}

Shape Game::getRandomShape()
{
   
    int randomIndex = rand() % shapes.size() + 1;
    shapeEnum randShapeEnum = shapes[randomIndex];
    Shape randShape = Shape(randShapeEnum);
    
    return randShape;
}

void Game::Draw(sf::RenderWindow& window)
{
    grid.Draw(window);
    grid.DrawInGame(window);
    DrawNextShape(window);
    DrawScore(window);
    DrawHold(window);
    DrawPortal(window);
    if(grid.shrink > 0)
    {
    window.draw(grid.ShrinkRect);
    }
    if(!gameOver)
    {
        currShape.Draw(window);
    }else
    {
        grid.DrawGameOver(window);
    }
    if(!currShape.rotateCounter)
    {
        DrawRotationWarning(window);
    }
}


void Game::handleInput(sf::Keyboard::Key key, sf::RenderWindow& window)
{
switch (key)
    {
    case sf::Keyboard::Left:
        MoveShapeLeft();  
        break;

    case sf::Keyboard::Down:
        MoveShapeDown();
        updateScore(0, 1);
        break;

    case sf::Keyboard::Right:
        MoveShapeRight();
        break;

    case sf::Keyboard::Up:
        RotateShape();
        BringShapeInside();
        break;

    case sf::Keyboard::H:
        HoldShape();
        break;

    case sf::Keyboard::Space:
        HardFall();
        break;       
    
    case sf::Keyboard::R:
        if(!gameOver)
        {
        Reset();
        }
        break;
    case sf::Keyboard::Enter:
        if(gameOver)
        {
            gameOver = false;
            Reset();
        }
    
    default:
        break;
}
}

void Game::MoveShapeLeft()
{
    if(!gameOver)
    {
        if(currShape.position.x > 0 && ShapeFitsLeft())
        {
        currShape.Move(-1, 0);
        }
    }
}

void Game::MoveShapeDown()
{  
    if(!gameOver)
    {
        if(currShape.position.y < 20 - currShape.shapeMatrix.size() && ShapeFitsDown())
        {
            currShape.Move(0, 1);
        }else
        {   
            LockShape();
        }
    }
}

void Game::MoveShapeRight()
{
    if(!gameOver)
    {
        if(currShape.position.x < 10 - currShape.shapeMatrix[0].size() && ShapeFitsRight())
        {
            currShape.Move(1, 0);
        }
    }
}

void Game::RotateShape()
{
    if(!gameOver)
    {
        bool flag = true;
        int newRow = currShape.shapeMatrix[0].size();
        int newCol = currShape.shapeMatrix.size();

        std::vector<std::vector<int>> newShapeMatrix(newRow, std::vector<int>(newCol));

        for(int i = 0; i < newRow; i++)
        {   
            for(int j = 0; j < newCol; j++)
            {
                newShapeMatrix[i][j] = currShape.shapeMatrix[j][i];
            }
        }

        for(int i = 0; i < newRow; i++)
        {
            for(int j = 0; j < newCol/2; j++)
            {
                std::swap(newShapeMatrix[i][j], newShapeMatrix[i][newCol - j - 1]);
            }
        }

        for(int i = 0; i < newShapeMatrix.size(); i++)
        {
            for(int j = 0; j < newShapeMatrix[0].size(); j++)
            {
                if(newShapeMatrix[i][j] != 0)
                {
                    if(grid.isCellEmpty(i + currShape.position.y, j + currShape.position.x) == false) 
                    {
                        flag = false;
                    }
                }
            }
        }
    
        if(flag && currShape.rotateCounter)
        {
            currShape.shapeMatrix = newShapeMatrix;
            rotateSound.play();
            currShape.rotateCounter--;
        }
    }
}

void Game::BringShapeInside()
{
    while(currShape.position.x > 10 - currShape.shapeMatrix[0].size())
    {
        MoveShapeLeft();
    }

    while (currShape.position.y > 20 - currShape.shapeMatrix.size())
    {
        currShape.Move(0, -1);
    }
}

void Game::LockShape()
{
    for(int i = 0; i < currShape.shapeMatrix.size(); i++)
    {
        for(int j = 0; j < currShape.shapeMatrix[0].size(); j++)
        {
            if(currShape.shapeMatrix[i][j] != 0)
            {
                if(grid.isCellEmpty(i + currShape.position.y, j + currShape.position.x) == false) 
                {
                    gameOver = true;
                    music.stop();
                }
            }
        }
    }

    auto colorP = std::find(colorLs.begin(), colorLs.end(), currShape.color);
    for(int i = 0; i < currShape.shapeMatrix.size(); i++)
    {
        for(int j = 0; j < currShape.shapeMatrix[0].size(); j++)
        {
            if(currShape.shapeMatrix[i][j] != 0)
            {
                grid.gridMatrix[i + currShape.position.y][j + currShape.position.x] = std::distance(colorLs.begin(), colorP);
            }
        }
    }

    currShape = nextShape;
    nextShape = getRandomShape();
    int rowsCleared = grid.ClearFullRows();
    updateScore(rowsCleared, 0);
}

bool Game::ShapeFitsDown()
{

    for(int i = 0; i < currShape.shapeMatrix.size(); i++)
    {
        for(int j = 0; j < currShape.shapeMatrix[0].size(); j++)
        {
            if(currShape.shapeMatrix[i][j] != 0)
            {
                if(!grid.isCellEmpty(i + 1 + currShape.position.y, j + currShape.position.x)) 
                {
                    return false;
                }else if(grid.isCellEmpty(i + 1 + currShape.position.y, j + currShape.position.x) == 2)
                {
                    currShape.Move(0, -1);
                    return true;
                }else if(currShape.position.x + j == randomCol && currShape.position.y + i == randomRow)
                {
                    CreatePortal();
                    HardFall();
                    return false;
                }

            }
        }
    }

    return true;
}

bool Game::ShapeFitsLeft()
{

    for(int i = 0; i < currShape.shapeMatrix.size(); i++)
    {
        for(int j = 0; j < currShape.shapeMatrix[0].size(); j++)
        {
            if(currShape.shapeMatrix[i][j] != 0)
            {
                if(grid.isCellEmpty(i + currShape.position.y, j - 1 + currShape.position.x) == false) 
                {
                    return false;
                }

            }
        }
    }

    return true;
}
bool Game::ShapeFitsRight()
{

    for(int i = 0; i < currShape.shapeMatrix.size(); i++)
    {
        for(int j = 0; j < currShape.shapeMatrix[0].size(); j++)
        {
            if(currShape.shapeMatrix[i][j] != 0)
            {
                if(grid.isCellEmpty(i + currShape.position.y, j + 1 + currShape.position.x) == false) 
                {
                    return false;
                }

            }
        }
    }

    return true;
}

void Game::Reset()
{
    grid.initGridMatrix();
    
    shapes = {plusSign, smallSquare, cornerPiece, tallTower, zigzag, uShape, stepShape, arrowUp, doubleZigzag, pyramid};
    
    currShape = getRandomShape();
    nextShape = getRandomShape();
    score = 0;
    music.play();
    isHolding = false;
    gameSpeed = 500;
    grid.shrink = 0;
    grid.shrinkDim = {300, 0};
    grid.shrinkWantedScore = 200;
}

void Game::CreatePortal(){

    randomRow = rand() % 10 + 5;
    randomCol = rand() % 9 + 1;

    while(grid.gridMatrix[randomRow][randomCol] != 0)
    {
        randomRow = rand() % 10 + 5;
        randomCol = rand() % 9 + 1;
    }
    
}

void Game::DrawPortal(sf::RenderWindow& window)
{
    if(grid.gridMatrix[randomRow][randomCol] != 0)
    {
        CreatePortal();
    }
    sf::RectangleShape portal;
    portal.setSize({30, 10});
    portal.setFillColor(sf::Color(116, 8, 128));
    portal.setPosition({static_cast<float>(200 + 30*(randomCol)),static_cast<float>(20 + 30*(randomRow+1))});
    window.draw(portal);
}

void Game::updateScore(int linesCleared, int movedDown)
{
    switch (linesCleared)
    {
    case 1:
        score += 100;
        break;
    
    case 2:
    score += 300;
        break;

    case 3:
        score += 500;
        break;
    
    default:
        break;
    }

    score += movedDown * 5;
}

void Game::DrawScore(sf::RenderWindow& window)
{
    sf::Font font;
    font.loadFromFile("source/fonts/8bit16.ttf");

    char scoreText[10];
    snprintf(scoreText, sizeof(scoreText), "%d", score);

    sf::Text gameScore(scoreText, font, 25);

    int scoreWidth = gameScore.getLocalBounds().width;
    int scoreHeight = gameScore.getLocalBounds().height;

    gameScore.setPosition(520 + ((150 - scoreWidth) / 2), 50 + ((50 - scoreHeight) / 2));

    gameScore.setFillColor(sf::Color::Black);

    window.draw(gameScore);
}

void Game::DrawNextShape(sf::RenderWindow& window)
{   
    int numRows = nextShape.shapeMatrix.size();
    int numCols = nextShape.shapeMatrix[0].size();

    for(int row = 0; row < numRows; row++)
    {
        for(int col = 0; col < numCols; col++)
        {
            int cellColorVal = nextShape.shapeMatrix[row][col];
            if(cellColorVal)
            {
            sf::RectangleShape cell;
            cell.setSize(sf::Vector2f(grid.cellSize - 1, grid.cellSize - 1));
            cell.setPosition(520 + ((150 - numCols * grid.cellSize) / 2) + col * grid.cellSize, 265 + ((150 - numRows * grid.cellSize) / 2) + row * grid.cellSize);
            cell.setFillColor(nextShape.color);
            
            window.draw(cell);   
            }
        }
    }
}

void Game::DrawRotationWarning(sf::RenderWindow& window)
{
    sf::Font font;
    font.loadFromFile("source/fonts/8bit16.ttf");

    sf::Text warning("Out of rotations!", font, 15);
    warning.setPosition(510, 550);
    warning.setFillColor(sf::Color::Red);

    window.draw(warning);
}

void Game::HoldShape()
{
    if(currShape.position.y < 6 && currShape.holdCounter && !gameOver)
    {
        if(!isHolding){
            holdShape = currShape;
            currShape = nextShape;
            nextShape = getRandomShape();
            isHolding = true;
            currShape.holdCounter--;
        }else
        {
            Shape tempShape = holdShape;
            holdShape = currShape;
            currShape = tempShape;
            currShape.position = {static_cast<int>(3 + 3 - currShape.shapeMatrix[0].size()), 0};
            currShape.holdCounter--;
            isHolding = true;
        }
    }
}

void Game::DrawHold(sf::RenderWindow& window)
{
    if(isHolding)
    {
        int numRows = holdShape.shapeMatrix.size();
        int numCols = holdShape.shapeMatrix[0].size();

        for(int row = 0; row < numRows; row++)
        {
            for(int col = 0; col < numCols; col++)
            {
                int cellColorVal = holdShape.shapeMatrix[row][col];
                if(cellColorVal)
                {
                sf::RectangleShape cell;
                cell.setSize(sf::Vector2f(grid.cellSize - 1, grid.cellSize - 1));
                cell.setPosition(20 + ((150 - numCols * grid.cellSize) / 2) + col * grid.cellSize, 55 + ((150 - numRows * grid.cellSize) / 2) + row * grid.cellSize);
                cell.setFillColor(holdShape.color);
            
                window.draw(cell);   
                }
            }
        }
    }
}

void Game::HardFall()
{

    while(ShapeFitsDown())
    {
        MoveShapeDown();
        updateScore(0, 1);
    }
}
