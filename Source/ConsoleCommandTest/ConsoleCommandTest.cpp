// Copyright Epic Games, Inc. All Rights Reserved.

#include "ConsoleCommandTest.h"
#include "ConsoleCommandTestObject.h"
#include "EngineUtils.h"
#include "Engine/Console.h"
#include "ConsoleSettings.h"

DEFINE_LOG_CATEGORY(LogConsoleCommandTest);

namespace ConsoleCommandTest
{
	static FAutoConsoleCommandWithWorld DumpActorNames
	(
		TEXT("Test.DumpActorNames"),
		TEXT("Logs the names of actors located in the currently open world."),
		FConsoleCommandWithWorldDelegate::CreateLambda([](UWorld* World)
		{
			check(IsValid(World));

			for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
			{
				const AActor* Actor = *Itr;
				UE_LOG(LogConsoleCommandTest, Log, TEXT("%s"), *GetNameSafe(Actor));
			}
		})
	);
	
	static FAutoConsoleCommandWithWorldAndArgs ReplaceActorLabels
	(
		TEXT("Test.ReplaceActorLabels"),
		TEXT("Replaces the specified string on the actor's label with the specified string."),
		FConsoleCommandWithWorldAndArgsDelegate::CreateLambda([](const TArray<FString>& Args, UWorld* World)
		{
			check(IsValid(World));

			if (Args.Num() < 2)
			{
				UE_LOG(LogConsoleCommandTest, Error, TEXT("Specify the character string before the change and the character string after the change in the argument."));
				return;
			}
			
			const FString& From = Args[0];
			const FString& To = Args[1];
			
			for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
			{
				AActor* Actor = *Itr;
				if (!IsValid(Actor))
				{
					continue;
				}

				const FString OriginalLabel = Actor->GetActorLabel();
				const FString ReplacedLabel = OriginalLabel.Replace(*From, *To);
				Actor->SetActorLabel(ReplacedLabel);

				if (OriginalLabel != ReplacedLabel)
				{
					UE_LOG(LogConsoleCommandTest, Log, TEXT("Renamed \"%s\" to \"%s\"."), *OriginalLabel, *ReplacedLabel);
				}
			}
		})
	);
}

void FConsoleCommandTest::StartupModule()
{
	BuildConsoleEntriesHandle = UConsole::RegisterConsoleAutoCompleteEntries.AddRaw(this, &FConsoleCommandTest::HandleRegisterConsoleAutoCompleteEntries);
}

void FConsoleCommandTest::ShutdownModule()
{
	UConsole::RegisterConsoleAutoCompleteEntries.Remove(BuildConsoleEntriesHandle);
}

bool FConsoleCommandTest::IsGameModule() const
{
	return true;
}

void FConsoleCommandTest::HandleRegisterConsoleAutoCompleteEntries(TArray<FAutoCompleteCommand>& AutoCompleteList) const
{
	auto AddAutoCompleteEntries = [&AutoCompleteList](const TArray<FString>& CommandElements) -> int32
	{
		const FString Command = FString::Join(CommandElements, TEXT(" "));
		int32 Index = 0;
		for (; Index < AutoCompleteList.Num(); Index++)
		{
			if (AutoCompleteList.IsValidIndex(Index))
			{
				if (AutoCompleteList[Index].Command == Command)
				{
					break;
				}
			}
		}

		FColor AutoCompleteCommandColor = FColor::Green;
		if (const auto* ConsoleSettings = GetDefault<UConsoleSettings>())
		{
			AutoCompleteCommandColor = ConsoleSettings->AutoCompleteCommandColor;
		}
		
		const int32 NewIndex = ((Index < AutoCompleteList.Num()) ? Index : AutoCompleteList.AddDefaulted());
		AutoCompleteList[NewIndex].Command = Command;
		AutoCompleteList[NewIndex].Color = AutoCompleteCommandColor;
		return NewIndex;
	};
	
	// AutoCompleteTest
	{
		const FString FunctionName = GET_FUNCTION_NAME_STRING_CHECKED(UConsoleCommandTestObject, AutoCompleteTest);
		const FString Description = TEXT("A test to try predictive conversion of console commands");
		
		{
			const int32 NewIndex = AddAutoCompleteEntries({ FunctionName });
			AutoCompleteList[NewIndex].Desc = Description;
		}
		
		if (const UEnum* Enum = StaticEnum<ETestCommandArg>())
		{
			for (int32 Index = 0; Index < Enum->NumEnums() - 1; Index++)
			{
				const FString EnumString = Enum->GetDisplayNameTextByIndex(Index).ToString();
				const int32 NewIndex = AddAutoCompleteEntries({ FunctionName, EnumString });
				AutoCompleteList[NewIndex].Desc = Description;
			}
		}
	}
}

IMPLEMENT_MODULE(FConsoleCommandTest, ConsoleCommandTest);
