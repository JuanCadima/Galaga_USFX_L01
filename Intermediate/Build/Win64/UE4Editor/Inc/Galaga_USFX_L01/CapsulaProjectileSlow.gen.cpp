// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Galaga_USFX_L01/CapsulaProjectileSlow.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCapsulaProjectileSlow() {}
// Cross Module References
	GALAGA_USFX_L01_API UClass* Z_Construct_UClass_ACapsulaProjectileSlow_NoRegister();
	GALAGA_USFX_L01_API UClass* Z_Construct_UClass_ACapsulaProjectileSlow();
	GALAGA_USFX_L01_API UClass* Z_Construct_UClass_AInventoryActor();
	UPackage* Z_Construct_UPackage__Script_Galaga_USFX_L01();
// End Cross Module References
	void ACapsulaProjectileSlow::StaticRegisterNativesACapsulaProjectileSlow()
	{
	}
	UClass* Z_Construct_UClass_ACapsulaProjectileSlow_NoRegister()
	{
		return ACapsulaProjectileSlow::StaticClass();
	}
	struct Z_Construct_UClass_ACapsulaProjectileSlow_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ACapsulaProjectileSlow_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AInventoryActor,
		(UObject* (*)())Z_Construct_UPackage__Script_Galaga_USFX_L01,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACapsulaProjectileSlow_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Input" },
		{ "IncludePath", "CapsulaProjectileSlow.h" },
		{ "ModuleRelativePath", "CapsulaProjectileSlow.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ACapsulaProjectileSlow_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACapsulaProjectileSlow>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ACapsulaProjectileSlow_Statics::ClassParams = {
		&ACapsulaProjectileSlow::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ACapsulaProjectileSlow_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ACapsulaProjectileSlow_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ACapsulaProjectileSlow()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ACapsulaProjectileSlow_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ACapsulaProjectileSlow, 3816188111);
	template<> GALAGA_USFX_L01_API UClass* StaticClass<ACapsulaProjectileSlow>()
	{
		return ACapsulaProjectileSlow::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ACapsulaProjectileSlow(Z_Construct_UClass_ACapsulaProjectileSlow, &ACapsulaProjectileSlow::StaticClass, TEXT("/Script/Galaga_USFX_L01"), TEXT("ACapsulaProjectileSlow"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACapsulaProjectileSlow);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
