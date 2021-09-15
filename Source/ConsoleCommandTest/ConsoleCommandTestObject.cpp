// Fill out your copyright notice in the Description page of Project Settings.

#include "ConsoleCommandTestObject.h"
#include "ConsoleCommandTest.h"

void UConsoleCommandTestObject::AutoCompleteTest(ETestCommandArg Type)
{
	if (const UEnum* Enum = StaticEnum<ETestCommandArg>())
	{
		const FString TypeString = Enum->GetDisplayValueAsText(Type).ToString();
	
		UE_LOG(LogConsoleCommandTest, Log, TEXT("%s : %s"), GET_FUNCTION_NAME_STRING_CHECKED(UConsoleCommandTestObject, AutoCompleteTest), *TypeString);
	}
}
