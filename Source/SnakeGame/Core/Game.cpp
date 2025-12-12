// Snake Game. Copyright Yura Kholodkov. All Rights Reserved.

#include "Core/Game.h"
#include "Grid.h"
#include "Core/Snake.h"
#include "Core/Food.h"

DEFINE_LOG_CATEGORY_STATIC(LogGame, All, All)

using namespace SnakeGame;

Game::Game(const Settings& settings) : c_settings(settings)
{
    m_grid = MakeShared<Grid>(settings.gridDims);
    checkf(m_grid->dim().width / 2 >= settings.snake.defaultSize, TEXT("Snake initial length [%i] doesn't fit grid width [%i]"),
        settings.snake.defaultSize, m_grid->dim().width);
    m_snake = MakeShared<Snake>(settings.snake);
    m_food = MakeShared<Food>();

    updateGrid();
    generateFood();
}

void Game::update(float deltaSeconds, const Input& input)
{
    if (m_gameOver || !updateTime(deltaSeconds)) return;
    move(input);
    if (died())
    {
        m_gameOver = true;
        UE_LOG(LogGame, Display, TEXT("------------------ GAME OVER ------------------"));
        UE_LOG(LogGame, Display, TEXT("------------------ SCORE: %i------------------"), m_score);
        return;
    }

    if (foodTaken())
    {
        ++m_score;
        m_snake->increase();
        generateFood();
    }
}

void Game::move(const Input& input)
{
    m_snake->move(input);
    updateGrid();
}

void Game::updateGrid()
{
    m_grid->update(m_snake->body(), CellType::Snake);
    m_grid->printDebug();
}

bool Game::updateTime(float deltaSeconds)
{
    m_moveSeconds += deltaSeconds;
    auto invertedGameSpeed = 1 / c_settings.gameSpeed;
    if (m_moveSeconds < invertedGameSpeed) return false;
    m_moveSeconds = 0.0f;
    return true;
}

bool Game::died() const
{
    return m_grid->hitTest(m_snake->head(), CellType::Wall) ||  //
           m_grid->hitTest(m_snake->head(), CellType::Snake);
}

void SnakeGame::Game::generateFood()
{
    Position foodPosition;
    if (m_grid->randomEmptyPosition(foodPosition))
    {
        m_food->setPosition(foodPosition);
        m_grid->update(m_food->position(), CellType::Food);
    }
    else
    {
        m_gameOver = true;
        UE_LOG(LogGame, Display, TEXT("------------------ GAME COMPLETED ------------------"));
        UE_LOG(LogGame, Display, TEXT("------------------ SCORE: %i------------------"), m_score);
    }
}

bool SnakeGame::Game::foodTaken() const
{
    return m_grid->hitTest(m_snake->head(), CellType::Food);
}
