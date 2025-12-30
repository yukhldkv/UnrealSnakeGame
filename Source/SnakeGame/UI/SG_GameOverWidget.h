// Snake Game. Copyright Yura Kholodkov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SG_GameOverWidget.generated.h"

class UTextBlock;

UCLASS()
class SNAKEGAME_API USG_GameOverWidget : public UUserWidget
{
    GENERATED_BODY()
    
protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> ScoreText;
    
public:
    void UpdateScore(uint32 Score);
};
