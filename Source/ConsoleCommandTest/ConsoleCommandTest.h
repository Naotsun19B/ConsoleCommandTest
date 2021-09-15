// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

struct FAutoCompleteCommand;

class FConsoleCommandTest : public IModuleInterface
{
public:
	// IModuleInterface interface.
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool IsGameModule() const override;
	// End of IModuleInterface interface.

private:
	// Register the predictive conversion of console commands.
	void HandleRegisterConsoleAutoCompleteEntries(TArray<FAutoCompleteCommand>& AutoCompleteList) const;

private:
	// Delegate handle for registering hot-reloaded classes that have been added.
	FDelegateHandle BuildConsoleEntriesHandle;
};

DECLARE_LOG_CATEGORY_EXTERN(LogConsoleCommandTest, Log, All);
