// Snake Game. Copyright Yura Kholodkov. All Rights Reserved.

#include "UI/SG_HUD.h"
#include "UI/SG_GameplayWidget.h"
#include "Core/Game.h"

void ASG_HUD::BeginPlay()
{
    Super::BeginPlay();

    GameplayWidget = CreateWidget<USG_GameplayWidget>(GetWorld(), GameplayWidgetClass);
    check(GameplayWidget);
    GameplayWidget->AddToViewport();
}

void ASG_HUD::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (Game.IsValid())
    {
        GameplayWidget->SetGameTime(Game.Pin()->gameTime());
    }
}

void ASG_HUD::SetModel(const TSharedPtr<SnakeGame::Game>& InGame)
{
    if (!InGame) return;

    Game = InGame;

    GameplayWidget->UpdateScore(InGame->score());

    using namespace SnakeGame;
    InGame->subscribeOnGameplayEvent(
        [&](GameplayEvent Event)
        {
            switch (Event)
            {
                case GameplayEvent::FoodTaken:  //
                    GameplayWidget->UpdateScore(InGame->score());
                    break;
            }
        });
}
