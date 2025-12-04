#pragma once

#include "Core/Types.h"
#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"

namespace SnakeGame
{
class WorldUtils
{
public:
    static FVector LinkPositionToVector(const SnakeGame::Position& Position, uint32 CellSize, const SnakeGame::Dim& Dims)
    {
        // position y needs to be inverted due to the way UE handles coordinate system
        return FVector((Dims.height - 1 - Position.y) * CellSize, Position.x * CellSize, 0.0)  //
               + FVector(CellSize * 0.5);  // shift snake location so that it fits the grid instead of moving on the gridlines
    }

    static void ScaleMesh(UStaticMeshComponent* Mesh, const FVector& WorldSize)
    {
        // scale mesh
        if (Mesh && Mesh->GetStaticMesh())
        {
            const FBox Box = Mesh->GetStaticMesh()->GetBoundingBox();
            const auto Size = Box.GetSize();

            check(Size.X);
            check(Size.Y);
            Mesh->SetRelativeScale3D(FVector(WorldSize / Size));
        }
    }
};
}  // namespace SnakeGame