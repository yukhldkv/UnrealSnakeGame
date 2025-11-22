// Snake Game. Copyright Yura Kholodkov. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SnakeGameEditorTarget : TargetRules
{
    public SnakeGameEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V6;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;

        ExtraModuleNames.AddRange(new string[] { "SnakeGame" });
    }
}
