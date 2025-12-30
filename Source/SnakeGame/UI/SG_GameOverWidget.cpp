// Snake Game. Copyright Yura Kholodkov. All Rights Reserved.

#include "UI/SG_GameOverWidget.h"
#include "Components/TextBlock.h"
#include "World/SG_WorldUtils.h"

void USG_GameOverWidget::SetScore(uint32 Score)
{
    if (ScoreText)
    {
        ScoreText->SetText(SnakeGame::WorldUtils::FormatScore(Score));
    }
}

void USG_GameOverWidget::SetResetKeyName(const FString& ResetKeyName)
{
    if (ResetText)
    {
        const FString ResetInfo = FString::Printf(TEXT("press <%s> to reset"), *ResetKeyName.ToLower());
        ResetText->SetText(FText::FromString(ResetInfo));
    }
}