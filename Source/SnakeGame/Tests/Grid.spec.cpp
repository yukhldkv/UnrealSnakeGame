// Snake Game. Copyright Yura Kholodkov. All Rights Reserved.

#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Core/Grid.h"

DEFINE_SPEC(
    FSnakeGrid, "Snake", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

void FSnakeGrid::Define()
{
    using namespace Snake;
    Describe("CoreGrid", [this]() { //
        It("DimsIncludeWalls", [this]()
        {
            const Grid grid(Dim{12, 10});
            TestTrueExpr(grid.dim().height == 12);
            TestTrueExpr(grid.dim().width == 14);
        }); });
}

#endif
