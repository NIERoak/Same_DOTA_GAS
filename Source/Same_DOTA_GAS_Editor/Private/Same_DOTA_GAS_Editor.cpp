// Copyright Epic Games, Inc. All Rights Reserved.

#include "Same_DOTA_GAS_Editor.h"





void FSame_DOTA_GAS_EditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	//在模块启动时注册一个资产操作到资产工具中
	
}

void FSame_DOTA_GAS_EditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSame_DOTA_GAS_EditorModule, Same_DOTA_GAS_Editor)