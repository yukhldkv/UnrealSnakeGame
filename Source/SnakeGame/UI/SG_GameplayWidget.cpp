// Snake Game. Copyright Yura Kholodkov. All Rights Reserved.

#include "SG_GameplayWidget.h"
#include "Components/TextBlock.h"
#include "World/SG_WorldUtils.h"

void USG_GameplayWidget::SetGameTime(float Seconds)
{
    if (TimeText)
    {
        TimeText->SetText(SnakeGame::WorldUtils::FormatSeconds(Seconds));
    }
}

void USG_GameplayWidget::SetScore(uint32 Score)
{
    if (ScoreText)
    {
        ScoreText->SetText(SnakeGame::WorldUtils::FormatScore(Score));
    }
}

void USG_GameplayWidget::SetResetKeyName(const FString& ResetKeyName)
{
    if (ResetText)
    {
        const FString ResetInfo = FString::Printf(TEXT("press <%s> to reset"), *ResetKeyName.ToLower());
        ResetText->SetText(FText::FromString(ResetInfo));
    }
}