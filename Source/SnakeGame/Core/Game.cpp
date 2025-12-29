// Snake Game. Copyright Yura Kholodkov. All Rights Reserved.

#include "Core/Game.h"
#include "Grid.h"
#include "Core/Snake.h"
#include "Core/Food.h"

DEFINE_LOG_CATEGORY_STATIC(LogGame, All, All)

using namespace SnakeGame;

Game::Game(const Settings& settings, const IPositionRandomizerPtr& randomizer) : c_settings(settings)
{
    m_grid = MakeShared<Grid>(settings.gridDims, randomizer);
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

    m_snake->move(input);

    if (died())
    {
        m_gameOver = true;
        dispatchEvent(GameplayEvent::GameOver);
        return;
    }

    if (foodTaken())
    {
        ++m_score;
        m_snake->increase();
        dispatchEvent(GameplayEvent::FoodTaken);
        generateFood();
    }

    updateGrid();
}

void Game::updateGrid()
{
    m_grid->update(m_snake->links().GetHead(), CellType::Snake);
    // m_grid->printDebug();
}

bool Game::updateTime(float deltaSeconds)
{
    m_gametime += deltaSeconds;
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
        dispatchEvent(GameplayEvent::GameCompleted);
        m_gameOver = true;
    }
}

bool SnakeGame::Game::foodTaken() const
{
    return m_grid->hitTest(m_snake->head(), CellType::Food);
}

void Game::subscribeOnGameplayEvent(GameplayEventCallback callback)
{
    m_gameplayEventCallbacks.Add(callback);
}

void Game::dispatchEvent(GameplayEvent Event)
{
    for (const auto& callback : m_gameplayEventCallbacks)
    {
        if (callback)
        {
            callback(Event);
        }
    }
}