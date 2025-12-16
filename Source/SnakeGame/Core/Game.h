// Snake Game. Copyright Yura Kholodkov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"

namespace SnakeGame
{

class Grid;
class Snake;
class Food;

class Game
{
public:
    Game(const Settings& settings);

    /**
     * Returns the pointer to the grid object
     * @return TTSharedPtr<Grid>  pointer to the grid object
     */
    TSharedPtr<Grid> grid() const { return m_grid; }

    TSharedPtr<Snake> snake() const { return m_snake; }

    TSharedPtr<Food> food() const { return m_food; }

    void update(float deltaSeconds, const Input& input);

    uint32 score() const { return m_score; }

    void subscribeOnGameplayEvent(GameplayEventCallback callback);

private:
    const Settings c_settings;
    TSharedPtr<Grid> m_grid;
    TSharedPtr<Snake> m_snake;
    TSharedPtr<Food> m_food;

    float m_moveSeconds{0.0f};
    bool m_gameOver{false};
    uint32 m_score{0};

    GameplayEventCallback m_gameplayEventCallback;

    void updateGrid();
    bool updateTime(float deltaSeconds);
    bool died() const;
    void generateFood();
    bool foodTaken() const;
};
}  // namespace SnakeGame