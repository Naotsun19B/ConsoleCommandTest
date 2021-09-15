// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ConsoleCommandTestObject.generated.h"

UENUM(BlueprintType)
enum class ETestCommandArg : uint8
{
	Unreal,
	Engine,
	Epic,
};

UCLASS()
class CONSOLECOMMANDTEST_API UConsoleCommandTestObject : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(Exec)
	static void AutoCompleteTest(ETestCommandArg Type);
};
