// Snake Game. Copyright Yura Kholodkov. All Rights Reserved.

#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Core/Grid.h"
#include "Core/Snake.h"

DEFINE_SPEC(
    FSnakeGrid, "Snake", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

void FSnakeGrid::Define()
{
    using namespace SnakeGame;
    Describe("Core.Grid",
        [this]()
        {
            It("DimsIncludeWalls",
                [this]()
                {
                    const Grid CoreGrid(Dim{12, 10});
                    TestTrueExpr(CoreGrid.dim().height == 12);
                    TestTrueExpr(CoreGrid.dim().width == 14);
                });
            It("CenterMightBeCalculatedCorrectly", [this]() { TestTrueExpr(Grid::center(13, 11) == Position(7, 6)); });
            It("HitTest.PositionMightBeUpdatedCorrectly.Food",
                [this]()
                {
                    Grid CoreGrid(Dim{12, 10});
                    TestTrueExpr(!CoreGrid.hitTest(Position(5, 5), CellType::Food));
                    CoreGrid.update(Position(5, 5), CellType::Food);
                    TestTrueExpr(CoreGrid.hitTest(Position(5, 5), CellType::Food));
                });
            It("HitTest.PositionMightBeUpdatedCorrectly.Snake",
                [this]()
                {
                    const Dim Dims = Dim{12, 10};
                    Settings::Snake Config;
                    Config.defaultSize = 4;
                    Config.startPosition = Grid::center(Dims.width, Dims.height);

                    Grid CoreGrid(Dim{12, 10});
                    auto CoreSnake = MakeShared<Snake>(Config);
                    CoreGrid.update(CoreSnake->links().GetHead(), CellType::Snake);

                    TestTrueExpr(CoreGrid.hitTest(Position(7, 6), CellType::Snake));
                    TestTrueExpr(CoreGrid.hitTest(Position(6, 6), CellType::Snake));
                    TestTrueExpr(CoreGrid.hitTest(Position(5, 6), CellType::Snake));
                    TestTrueExpr(CoreGrid.hitTest(Position(4, 6), CellType::Snake));
                });
            It("HitTest.CellReleaseMightBeCorrect",
                [this]()
                {
                    Grid CoreGrid(Dim{12, 10});
                    CoreGrid.update(Position(5, 5), CellType::Food);
                    TestTrueExpr(CoreGrid.hitTest(Position(5, 5), CellType::Food));

                    CoreGrid.update(Position(5, 6), CellType::Food);
                    TestTrueExpr(CoreGrid.hitTest(Position(5, 5), CellType::Empty));
                    TestTrueExpr(CoreGrid.hitTest(Position(5, 6), CellType::Food));
                });

            It("EmptyCellForFoodMightBeFound",
                [this]()
                {
                    Grid CoreGrid(Dim{2, 2});
                    TSnakeList Links;
                    Links.AddTail(Position(1, 1));
                    Links.AddTail(Position(1, 2));
                    Links.AddTail(Position(2, 1));
                    CoreGrid.update(Links.GetHead(), CellType::Snake);

                    Position foodPosition;
                    const bool Found = CoreGrid.randomEmptyPosition(foodPosition);
                    TestTrueExpr(Found);
                    TestTrueExpr(foodPosition == Position(2, 2));
                });

            // game completed, no empty cells for food generation
            It("EmptyCellForFoodCannotBeFoundWhenSnakeFillsGrid",
                [this]()
                {
                    Grid CoreGrid(Dim{2, 2});
                    TSnakeList Links;
                    Links.AddTail(Position(1, 1));
                    Links.AddTail(Position(1, 2));
                    Links.AddTail(Position(2, 1));
                    Links.AddTail(Position(2, 2));
                    CoreGrid.update(Links.GetHead(), CellType::Snake);

                    Position foodPosition;
                    const bool Found = CoreGrid.randomEmptyPosition(foodPosition);
                    TestTrueExpr(!Found);
                });
        });
}

#endif
