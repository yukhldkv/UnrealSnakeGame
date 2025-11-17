// Snake Game. Copyright Yura Kholodkov. All Rights Reserved.

#include "Framework/SG_Pawn.h"
#include "Camera/CameraComponent.h"

namespace
{
double HalfFOVTan(double FOVDegrees)
{
    return FMath::Tan(FMath::DegreesToRadians(FOVDegrees * 0.5));
}

double VerticalFOV(double HorFOVDegrees, double ViewportAspectHW)
{
    return FMath::RadiansToDegrees  //
        (2.0 * FMath::Atan(FMath::Tan(FMath::DegreesToRadians(HorFOVDegrees) * 0.5) * ViewportAspectHW));
}

constexpr double GridMargin = 2.0;

}  // namespace

ASG_Pawn::ASG_Pawn()
{
    PrimaryActorTick.bCanEverTick = false;

    Origin = CreateDefaultSubobject<USceneComponent>("Origin");
    check(Origin);
    SetRootComponent(Origin);

    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    check(Camera);
    Camera->SetupAttachment(GetRootComponent());
    Camera->AddRelativeRotation(FRotator(-90, 0, 0));
    Camera->bOverrideAspectRatioAxisConstraint = true;
}

void ASG_Pawn::UpdateLocation(const Snake::Dim& InDim, int32 InCellSize, const FTransform& InGridOrigin)
{
    Dim = InDim;
    CellSize = InCellSize;
    GridOrigin = InGridOrigin;

    auto* Viewport = GEngine->GameViewport->Viewport;
    Viewport->ViewportResizedEvent.Remove(ResizeHandle);
    ResizeHandle = Viewport->ViewportResizedEvent.AddUObject(this, &ASG_Pawn::OnViewportResized);

#if WITH_EDITOR
    OnViewportResized(Viewport, 0);
#endif
}

void ASG_Pawn::OnViewportResized(FViewport* Viewport, uint32 Val)
{
    if (!Viewport || Viewport->GetSizeXY().Y == 0 || Dim.height == 0) return;

    const double WorldWidth = Dim.width * CellSize;
    const double WorldHeight = Dim.height * CellSize;
    double LocationZ = 0.0;
    const double ViewportAspect = static_cast<double>(Viewport->GetSizeXY().X) / Viewport->GetSizeXY().Y;
    const double GridAspect = static_cast<double>(Dim.width) / Dim.height;

    if (ViewportAspect <= GridAspect)
    {
        const double MarginWidth = (Dim.width + GridMargin) * CellSize;
        LocationZ = MarginWidth * 0.5 / HalfFOVTan(Camera->FieldOfView);
    }
    else
    {
        check(ViewportAspect);
        const double VFOV = VerticalFOV(Camera->FieldOfView, 1.0 / ViewportAspect);
        const double MarginHeight = (Dim.height + GridMargin) * CellSize;
        LocationZ = MarginHeight * 0.5 / HalfFOVTan(VFOV);
    }

    const FVector NewPawnLocation =
        GridOrigin.GetLocation() + FVector(0.5 * WorldHeight, 0.5 * WorldWidth, LocationZ);
    SetActorLocation(NewPawnLocation);
}