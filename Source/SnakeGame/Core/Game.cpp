// Snake Game. Copyright Yura Kholodkov. All Rights Reserved.

#include "Core/Game.h"
#include "Grid.h"

DEFINE_LOG_CATEGORY_STATIC(LogGame, All, All)

using namespace Snake;

Game::Game(const Settings& settings) : c_settings(settings)
{
    m_grid = MakeShared<Grid>(settings.gridDims);
}
