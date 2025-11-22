// Snake Game. Copyright Yura Kholodkov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Types.h"
#include "World/SG_WorldTypes.h"
#include "SG_Grid.generated.h"

namespace SnakeGame
{
class Grid;
}

class UStaticMeshComponent;

UCLASS()
class SNAKEGAME_API ASG_Grid : public AActor
{
    GENERATED_BODY()

public:
    ASG_Grid();

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Origin;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* GridMesh;

    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    /**
     * Set core model to be observed by the grid world actor
     * @param Grid  model object
     * @param CellSize  world size of the cell
     */
    void SetModel(const TSharedPtr<SnakeGame::Grid>& Grid, uint32 CellSize);

    void UpdateColors(const FSnakeColors& Colors);

private:
    UPROPERTY()
    UMaterialInstanceDynamic* GridMaterial;

    SnakeGame::Dim GridDim;
    uint32 CellSize;
    uint32 WorldWidth;
    uint32 WorldHeight;

    void DrawGrid();
};
