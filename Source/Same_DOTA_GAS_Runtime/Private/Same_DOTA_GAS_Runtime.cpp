// Copyright Epic Games, Inc. All Rights Reserved.

#include "Same_DOTA_GAS_Runtime.h"


#define LOCTEXT_NAMESPACE "FSame_DOTA_GAS_RuntimeModule"

void FSame_DOTA_GAS_RuntimeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FSame_DOTA_GAS_RuntimeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSame_DOTA_GAS_RuntimeModule, Same_DOTA_GAS_Runtime)