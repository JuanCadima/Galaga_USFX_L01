// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Galaga_USFX_L01/NaveAyudante.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNaveAyudante() {}
// Cross Module References
	GALAGA_USFX_L01_API UClass* Z_Construct_UClass_ANaveAyudante_NoRegister();
	GALAGA_USFX_L01_API UClass* Z_Construct_UClass_ANaveAyudante();
	GALAGA_USFX_L01_API UClass* Z_Construct_UClass_AGalaga_USFX_L01Pawn();
	UPackage* Z_Construct_UPackage__Script_Galaga_USFX_L01();
// End Cross Module References
	void ANaveAyudante::StaticRegisterNativesANaveAyudante()
	{
	}
	UClass* Z_Construct_UClass_ANaveAyudante_NoRegister()
	{
		return ANaveAyudante::StaticClass();
	}
	struct Z_Construct_UClass_ANaveAyudante_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ANaveAyudante_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGalaga_USFX_L01Pawn,
		(UObject* (*)())Z_Construct_UPackage__Script_Galaga_USFX_L01,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ANaveAyudante_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "NaveAyudante.h" },
		{ "ModuleRelativePath", "NaveAyudante.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ANaveAyudante_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ANaveAyudante>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ANaveAyudante_Statics::ClassParams = {
		&ANaveAyudante::StaticClass,
		"Game",
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
		METADATA_PARAMS(Z_Construct_UClass_ANaveAyudante_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ANaveAyudante_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ANaveAyudante()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ANaveAyudante_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ANaveAyudante, 1833340137);
	template<> GALAGA_USFX_L01_API UClass* StaticClass<ANaveAyudante>()
	{
		return ANaveAyudante::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ANaveAyudante(Z_Construct_UClass_ANaveAyudante, &ANaveAyudante::StaticClass, TEXT("/Script/Galaga_USFX_L01"), TEXT("ANaveAyudante"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ANaveAyudante);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
