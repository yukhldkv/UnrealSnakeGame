// Snake Game. Copyright Yura Kholodkov. All Rights Reserved.

#include "UI/SG_GameOverWidget.h"
#include "Components/TextBlock.h"
#include "World/SG_WorldUtils.h"

void USG_GameOverWidget::UpdateScore(uint32 Score)
{
    if (ScoreText)
    {
        ScoreText->SetText(SnakeGame::WorldUtils::FormatScore(Score));
    }
}