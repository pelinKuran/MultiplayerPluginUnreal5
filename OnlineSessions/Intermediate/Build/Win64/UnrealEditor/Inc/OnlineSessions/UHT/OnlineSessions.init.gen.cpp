// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeOnlineSessions_init() {}
	ONLINESESSIONS_API UFunction* Z_Construct_UDelegateFunction_OnlineSessions_MultiplayerOnCreateSessionComplete__DelegateSignature();
	ONLINESESSIONS_API UFunction* Z_Construct_UDelegateFunction_OnlineSessions_MultiplayerOnDestroySessionComplete__DelegateSignature();
	ONLINESESSIONS_API UFunction* Z_Construct_UDelegateFunction_OnlineSessions_MultiplayerOnStartSessionComplete__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_OnlineSessions;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_OnlineSessions()
	{
		if (!Z_Registration_Info_UPackage__Script_OnlineSessions.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_OnlineSessions_MultiplayerOnCreateSessionComplete__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_OnlineSessions_MultiplayerOnDestroySessionComplete__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_OnlineSessions_MultiplayerOnStartSessionComplete__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/OnlineSessions",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x7A39F614,
				0x2AECA759,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_OnlineSessions.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_OnlineSessions.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_OnlineSessions(Z_Construct_UPackage__Script_OnlineSessions, TEXT("/Script/OnlineSessions"), Z_Registration_Info_UPackage__Script_OnlineSessions, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x7A39F614, 0x2AECA759));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
