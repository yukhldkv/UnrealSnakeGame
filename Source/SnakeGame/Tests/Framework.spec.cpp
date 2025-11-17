// Snake Game. Copyright Yura Kholodkov. All Rights Reserved.

#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Tests/Utils/TestUtils.h"
#include "Framework/SG_GameMode.h"
#include "Framework/SG_Pawn.h"

BEGIN_DEFINE_SPEC(FSnakeFramework, "Snake",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
UWorld* World;
END_DEFINE_SPEC(FSnakeFramework)

void FSnakeFramework::Define()
{
    using namespace LifeExe::Test;

    Describe("Framework", [this]() { //
        BeforeEach([this]()
        {
           AutomationOpenMap("GameLevel");
            World = GetTestGameWorld();
        });
        It("GameMapShouldExist", [this]()
        {
            TestNotNull("World Exists", World);
        });
        It("ClassesMightBeSetupCorrectly", [this]()
        {
            TestNotNull("Snake game mode set up", Cast<ASG_GameMode>(World->GetAuthGameMode()));
            TestNotNull("Snake pawn set up", Cast<ASG_Pawn>(World->GetFirstPlayerController()->GetPawn()));
        });
        xIt("PawnLocationShouldBeAdjustedCorrectly", [this](){ unimplemented(); });
    });
}

#endif
