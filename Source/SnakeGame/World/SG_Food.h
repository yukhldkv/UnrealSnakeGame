// Snake Game. Copyright Yura Kholodkov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Food.h"
#include "SG_Food.generated.h"

class UStaticMeshComponent;
class UNiagaraSystem;

UCLASS()
class SNAKEGAME_API ASG_Food : public AActor
{
    GENERATED_BODY()

public:
    ASG_Food();

    void SetModel(const TSharedPtr<SnakeGame::Food>& Food, uint32 CellSize, const SnakeGame::Dim& Dims);
    void UpdateColors(const FLinearColor& Color);
    void Explode();

    FVector GetFoodWorldLocation() const;

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Origin;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* FoodMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TObjectPtr<UNiagaraSystem> ExplosionEffect;

public:
    virtual void Tick(float DeltaTime) override;

private:
    TWeakPtr<SnakeGame::Food> Food;
    uint32 CellSize;
    SnakeGame::Dim Dims;
    FLinearColor FoodColor;
};
