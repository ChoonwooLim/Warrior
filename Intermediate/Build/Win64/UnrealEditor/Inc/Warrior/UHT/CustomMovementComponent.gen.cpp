// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Warrior/Public/Components/CustomMovementComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCustomMovementComponent() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UCharacterMovementComponent();
	ENGINE_API UEnum* Z_Construct_UEnum_Engine_EObjectTypeQuery();
	UPackage* Z_Construct_UPackage__Script_Warrior();
	WARRIOR_API UClass* Z_Construct_UClass_UCustomMovementComponent();
	WARRIOR_API UClass* Z_Construct_UClass_UCustomMovementComponent_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(UCustomMovementComponent::execCheckObstacleAhead)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->CheckObstacleAhead();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCustomMovementComponent::execIsGroundBelow)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->IsGroundBelow();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCustomMovementComponent::execIsCeilingAbove)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->IsCeilingAbove();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCustomMovementComponent::execCheckFlightCondition)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->CheckFlightCondition();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCustomMovementComponent::execCheckSwimmingCondition)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->CheckSwimmingCondition();
		P_NATIVE_END;
	}
	void UCustomMovementComponent::StaticRegisterNativesUCustomMovementComponent()
	{
		UClass* Class = UCustomMovementComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CheckFlightCondition", &UCustomMovementComponent::execCheckFlightCondition },
			{ "CheckObstacleAhead", &UCustomMovementComponent::execCheckObstacleAhead },
			{ "CheckSwimmingCondition", &UCustomMovementComponent::execCheckSwimmingCondition },
			{ "IsCeilingAbove", &UCustomMovementComponent::execIsCeilingAbove },
			{ "IsGroundBelow", &UCustomMovementComponent::execIsGroundBelow },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UCustomMovementComponent_CheckFlightCondition_Statics
	{
		struct CustomMovementComponent_eventCheckFlightCondition_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UCustomMovementComponent_CheckFlightCondition_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((CustomMovementComponent_eventCheckFlightCondition_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCustomMovementComponent_CheckFlightCondition_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(CustomMovementComponent_eventCheckFlightCondition_Parms), &Z_Construct_UFunction_UCustomMovementComponent_CheckFlightCondition_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCustomMovementComponent_CheckFlightCondition_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCustomMovementComponent_CheckFlightCondition_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCustomMovementComponent_CheckFlightCondition_Statics::Function_MetaDataParams[] = {
		{ "Category", "Character Movement: Flying" },
		{ "ModuleRelativePath", "Public/Components/CustomMovementComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCustomMovementComponent_CheckFlightCondition_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCustomMovementComponent, nullptr, "CheckFlightCondition", nullptr, nullptr, Z_Construct_UFunction_UCustomMovementComponent_CheckFlightCondition_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCustomMovementComponent_CheckFlightCondition_Statics::PropPointers), sizeof(Z_Construct_UFunction_UCustomMovementComponent_CheckFlightCondition_Statics::CustomMovementComponent_eventCheckFlightCondition_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCustomMovementComponent_CheckFlightCondition_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCustomMovementComponent_CheckFlightCondition_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCustomMovementComponent_CheckFlightCondition_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UCustomMovementComponent_CheckFlightCondition_Statics::CustomMovementComponent_eventCheckFlightCondition_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UCustomMovementComponent_CheckFlightCondition()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCustomMovementComponent_CheckFlightCondition_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCustomMovementComponent_CheckObstacleAhead_Statics
	{
		struct CustomMovementComponent_eventCheckObstacleAhead_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UCustomMovementComponent_CheckObstacleAhead_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((CustomMovementComponent_eventCheckObstacleAhead_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCustomMovementComponent_CheckObstacleAhead_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(CustomMovementComponent_eventCheckObstacleAhead_Parms), &Z_Construct_UFunction_UCustomMovementComponent_CheckObstacleAhead_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCustomMovementComponent_CheckObstacleAhead_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCustomMovementComponent_CheckObstacleAhead_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCustomMovementComponent_CheckObstacleAhead_Statics::Function_MetaDataParams[] = {
		{ "Category", "Character Movement: Flying" },
		{ "ModuleRelativePath", "Public/Components/CustomMovementComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCustomMovementComponent_CheckObstacleAhead_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCustomMovementComponent, nullptr, "CheckObstacleAhead", nullptr, nullptr, Z_Construct_UFunction_UCustomMovementComponent_CheckObstacleAhead_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCustomMovementComponent_CheckObstacleAhead_Statics::PropPointers), sizeof(Z_Construct_UFunction_UCustomMovementComponent_CheckObstacleAhead_Statics::CustomMovementComponent_eventCheckObstacleAhead_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCustomMovementComponent_CheckObstacleAhead_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCustomMovementComponent_CheckObstacleAhead_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCustomMovementComponent_CheckObstacleAhead_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UCustomMovementComponent_CheckObstacleAhead_Statics::CustomMovementComponent_eventCheckObstacleAhead_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UCustomMovementComponent_CheckObstacleAhead()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCustomMovementComponent_CheckObstacleAhead_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCustomMovementComponent_CheckSwimmingCondition_Statics
	{
		struct CustomMovementComponent_eventCheckSwimmingCondition_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UCustomMovementComponent_CheckSwimmingCondition_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((CustomMovementComponent_eventCheckSwimmingCondition_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCustomMovementComponent_CheckSwimmingCondition_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(CustomMovementComponent_eventCheckSwimmingCondition_Parms), &Z_Construct_UFunction_UCustomMovementComponent_CheckSwimmingCondition_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCustomMovementComponent_CheckSwimmingCondition_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCustomMovementComponent_CheckSwimmingCondition_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCustomMovementComponent_CheckSwimmingCondition_Statics::Function_MetaDataParams[] = {
		{ "Category", "Character Movement: Swimming" },
		{ "ModuleRelativePath", "Public/Components/CustomMovementComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCustomMovementComponent_CheckSwimmingCondition_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCustomMovementComponent, nullptr, "CheckSwimmingCondition", nullptr, nullptr, Z_Construct_UFunction_UCustomMovementComponent_CheckSwimmingCondition_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCustomMovementComponent_CheckSwimmingCondition_Statics::PropPointers), sizeof(Z_Construct_UFunction_UCustomMovementComponent_CheckSwimmingCondition_Statics::CustomMovementComponent_eventCheckSwimmingCondition_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCustomMovementComponent_CheckSwimmingCondition_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCustomMovementComponent_CheckSwimmingCondition_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCustomMovementComponent_CheckSwimmingCondition_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UCustomMovementComponent_CheckSwimmingCondition_Statics::CustomMovementComponent_eventCheckSwimmingCondition_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UCustomMovementComponent_CheckSwimmingCondition()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCustomMovementComponent_CheckSwimmingCondition_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCustomMovementComponent_IsCeilingAbove_Statics
	{
		struct CustomMovementComponent_eventIsCeilingAbove_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UCustomMovementComponent_IsCeilingAbove_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((CustomMovementComponent_eventIsCeilingAbove_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCustomMovementComponent_IsCeilingAbove_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(CustomMovementComponent_eventIsCeilingAbove_Parms), &Z_Construct_UFunction_UCustomMovementComponent_IsCeilingAbove_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCustomMovementComponent_IsCeilingAbove_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCustomMovementComponent_IsCeilingAbove_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCustomMovementComponent_IsCeilingAbove_Statics::Function_MetaDataParams[] = {
		{ "Category", "Character Movement: Flying" },
		{ "ModuleRelativePath", "Public/Components/CustomMovementComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCustomMovementComponent_IsCeilingAbove_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCustomMovementComponent, nullptr, "IsCeilingAbove", nullptr, nullptr, Z_Construct_UFunction_UCustomMovementComponent_IsCeilingAbove_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCustomMovementComponent_IsCeilingAbove_Statics::PropPointers), sizeof(Z_Construct_UFunction_UCustomMovementComponent_IsCeilingAbove_Statics::CustomMovementComponent_eventIsCeilingAbove_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCustomMovementComponent_IsCeilingAbove_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCustomMovementComponent_IsCeilingAbove_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCustomMovementComponent_IsCeilingAbove_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UCustomMovementComponent_IsCeilingAbove_Statics::CustomMovementComponent_eventIsCeilingAbove_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UCustomMovementComponent_IsCeilingAbove()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCustomMovementComponent_IsCeilingAbove_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCustomMovementComponent_IsGroundBelow_Statics
	{
		struct CustomMovementComponent_eventIsGroundBelow_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UCustomMovementComponent_IsGroundBelow_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((CustomMovementComponent_eventIsGroundBelow_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCustomMovementComponent_IsGroundBelow_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(CustomMovementComponent_eventIsGroundBelow_Parms), &Z_Construct_UFunction_UCustomMovementComponent_IsGroundBelow_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCustomMovementComponent_IsGroundBelow_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCustomMovementComponent_IsGroundBelow_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCustomMovementComponent_IsGroundBelow_Statics::Function_MetaDataParams[] = {
		{ "Category", "Character Movement: Flying" },
		{ "ModuleRelativePath", "Public/Components/CustomMovementComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCustomMovementComponent_IsGroundBelow_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCustomMovementComponent, nullptr, "IsGroundBelow", nullptr, nullptr, Z_Construct_UFunction_UCustomMovementComponent_IsGroundBelow_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCustomMovementComponent_IsGroundBelow_Statics::PropPointers), sizeof(Z_Construct_UFunction_UCustomMovementComponent_IsGroundBelow_Statics::CustomMovementComponent_eventIsGroundBelow_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCustomMovementComponent_IsGroundBelow_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCustomMovementComponent_IsGroundBelow_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCustomMovementComponent_IsGroundBelow_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UCustomMovementComponent_IsGroundBelow_Statics::CustomMovementComponent_eventIsGroundBelow_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UCustomMovementComponent_IsGroundBelow()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCustomMovementComponent_IsGroundBelow_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCustomMovementComponent);
	UClass* Z_Construct_UClass_UCustomMovementComponent_NoRegister()
	{
		return UCustomMovementComponent::StaticClass();
	}
	struct Z_Construct_UClass_UCustomMovementComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UECodeGen_Private::FBytePropertyParams NewProp_ClimbableSurfaceTraceTypes_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ClimbableSurfaceTraceTypes_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ClimbableSurfaceTraceTypes;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ClimbCapsuleTraceRadius_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ClimbCapsuleTraceRadius;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ClimbCapsuleTraceHalfHeight_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ClimbCapsuleTraceHalfHeight;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SwimTraceRadius_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_SwimTraceRadius;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SwimTraceDepth_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_SwimTraceDepth;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FlightTraceDistance_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_FlightTraceDistance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CeilingTraceDistance_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_CeilingTraceDistance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GroundTraceDistance_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_GroundTraceDistance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ObstacleTraceDistance_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ObstacleTraceDistance;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCustomMovementComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UCharacterMovementComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_Warrior,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomMovementComponent_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UCustomMovementComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UCustomMovementComponent_CheckFlightCondition, "CheckFlightCondition" }, // 3492110002
		{ &Z_Construct_UFunction_UCustomMovementComponent_CheckObstacleAhead, "CheckObstacleAhead" }, // 1231577013
		{ &Z_Construct_UFunction_UCustomMovementComponent_CheckSwimmingCondition, "CheckSwimmingCondition" }, // 2560194188
		{ &Z_Construct_UFunction_UCustomMovementComponent_IsCeilingAbove, "IsCeilingAbove" }, // 1414038408
		{ &Z_Construct_UFunction_UCustomMovementComponent_IsGroundBelow, "IsGroundBelow" }, // 3184024585
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomMovementComponent_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCustomMovementComponent_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Components/CustomMovementComponent.h" },
		{ "ModuleRelativePath", "Public/Components/CustomMovementComponent.h" },
	};
#endif
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbableSurfaceTraceTypes_Inner = { "ClimbableSurfaceTraceTypes", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UEnum_Engine_EObjectTypeQuery, METADATA_PARAMS(0, nullptr) }; // 3930035403
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbableSurfaceTraceTypes_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Character Movement: Climbing" },
		{ "ModuleRelativePath", "Public/Components/CustomMovementComponent.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbableSurfaceTraceTypes = { "ClimbableSurfaceTraceTypes", nullptr, (EPropertyFlags)0x0040000000010015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCustomMovementComponent, ClimbableSurfaceTraceTypes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbableSurfaceTraceTypes_MetaData), Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbableSurfaceTraceTypes_MetaData) }; // 3930035403
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbCapsuleTraceRadius_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Character Movement: Climbing" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/*\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd: DoCapsuleTraceMultiByObject()\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xee\xb6\xb2 \xc5\xb8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcf\xb4\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd.\n               EObjectTypeQuery\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xf0\xb8\xae\xbe\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xe6\xb5\xb9 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd6\xb4\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xc5\xb8\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd(Enum) \xef\xbf\xbd\xcc\xb4\xef\xbf\xbd.\n\x09 \xef\xbf\xbd\xc7\xb9\xef\xbf\xbd: \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xb0\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc5\xb8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd(Static Mesh)\xef\xbf\xbd\xcc\xb3\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd(Physics Body) \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd8\xbe\xef\xbf\xbd \xef\xbf\xbd\xcf\xb4\xc2\xb5\xef\xbf\xbd,\n             ClimbableSurfaceTraceTypes\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcf\xbf\xef\xbf\xbd \xc6\xaf\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd6\xb5\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xb8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd.*/" },
#endif
		{ "ModuleRelativePath", "Public/Components/CustomMovementComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd: DoCapsuleTraceMultiByObject()\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xee\xb6\xb2 \xc5\xb8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcf\xb4\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd.\n               EObjectTypeQuery\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xf0\xb8\xae\xbe\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xe6\xb5\xb9 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd6\xb4\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xc5\xb8\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd(Enum) \xef\xbf\xbd\xcc\xb4\xef\xbf\xbd.\n        \xef\xbf\xbd\xc7\xb9\xef\xbf\xbd: \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xb0\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc5\xb8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd(Static Mesh)\xef\xbf\xbd\xcc\xb3\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd(Physics Body) \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd8\xbe\xef\xbf\xbd \xef\xbf\xbd\xcf\xb4\xc2\xb5\xef\xbf\xbd,\n             ClimbableSurfaceTraceTypes\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcf\xbf\xef\xbf\xbd \xc6\xaf\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd6\xb5\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xb8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd." },
#endif
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbCapsuleTraceRadius = { "ClimbCapsuleTraceRadius", nullptr, (EPropertyFlags)0x0040000000010015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCustomMovementComponent, ClimbCapsuleTraceRadius), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbCapsuleTraceRadius_MetaData), Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbCapsuleTraceRadius_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbCapsuleTraceHalfHeight_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Character Movement: Climbing" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/*\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd: CapsuleTraceMultiForObjects() \xef\xbf\xbd\xd4\xbc\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcf\xb4\xef\xbf\xbd \xc4\xb8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd.\n              \xef\xbf\xbd\xef\xbf\xbd, \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xe6\xbf\xa1\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc4\xb8\xef\xbf\xbd\xef\xbf\xbd \xc5\xa9\xef\xbf\xbd\xe2\xb8\xa6 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcf\xb4\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd.\n      \xef\xbf\xbd\xc7\xb9\xef\xbf\xbd: \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc5\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd, \xef\xbf\xbd\xca\xb9\xef\xbf\xbd \xc5\xa9\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xca\xb4\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd.\n              \xef\xbf\xbd\xe2\xba\xbb\xef\xbf\xbd\xef\xbf\xbd 50.f \xef\xbf\xbd\xef\xbf\xbd \xc4\xb8\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd 50cm.*/" },
#endif
		{ "ModuleRelativePath", "Public/Components/CustomMovementComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd: CapsuleTraceMultiForObjects() \xef\xbf\xbd\xd4\xbc\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcf\xb4\xef\xbf\xbd \xc4\xb8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd.\n              \xef\xbf\xbd\xef\xbf\xbd, \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xe6\xbf\xa1\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc4\xb8\xef\xbf\xbd\xef\xbf\xbd \xc5\xa9\xef\xbf\xbd\xe2\xb8\xa6 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcf\xb4\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd.\n      \xef\xbf\xbd\xc7\xb9\xef\xbf\xbd: \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc5\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd, \xef\xbf\xbd\xca\xb9\xef\xbf\xbd \xc5\xa9\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xca\xb4\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd.\n              \xef\xbf\xbd\xe2\xba\xbb\xef\xbf\xbd\xef\xbf\xbd 50.f \xef\xbf\xbd\xef\xbf\xbd \xc4\xb8\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd 50cm." },
#endif
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbCapsuleTraceHalfHeight = { "ClimbCapsuleTraceHalfHeight", nullptr, (EPropertyFlags)0x0040000000010015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCustomMovementComponent, ClimbCapsuleTraceHalfHeight), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbCapsuleTraceHalfHeight_MetaData), Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbCapsuleTraceHalfHeight_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_SwimTraceRadius_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Character Movement: Swimming" },
		{ "ModuleRelativePath", "Public/Components/CustomMovementComponent.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_SwimTraceRadius = { "SwimTraceRadius", nullptr, (EPropertyFlags)0x0040000000010015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCustomMovementComponent, SwimTraceRadius), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_SwimTraceRadius_MetaData), Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_SwimTraceRadius_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_SwimTraceDepth_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Character Movement: Swimming" },
		{ "ModuleRelativePath", "Public/Components/CustomMovementComponent.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_SwimTraceDepth = { "SwimTraceDepth", nullptr, (EPropertyFlags)0x0040000000010015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCustomMovementComponent, SwimTraceDepth), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_SwimTraceDepth_MetaData), Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_SwimTraceDepth_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_FlightTraceDistance_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Character Movement: Flying" },
		{ "ModuleRelativePath", "Public/Components/CustomMovementComponent.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_FlightTraceDistance = { "FlightTraceDistance", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCustomMovementComponent, FlightTraceDistance), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_FlightTraceDistance_MetaData), Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_FlightTraceDistance_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_CeilingTraceDistance_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Character Movement: Flying" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xce\xb8\xef\xbf\xbd \xc3\xbc\xc5\xa9\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xc5\xb8\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Public/Components/CustomMovementComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xce\xb8\xef\xbf\xbd \xc3\xbc\xc5\xa9\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xc5\xb8\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_CeilingTraceDistance = { "CeilingTraceDistance", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCustomMovementComponent, CeilingTraceDistance), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_CeilingTraceDistance_MetaData), Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_CeilingTraceDistance_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_GroundTraceDistance_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Character Movement: Flying" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xc3\xb5\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xc5\xb8\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Public/Components/CustomMovementComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xc3\xb5\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xc5\xb8\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_GroundTraceDistance = { "GroundTraceDistance", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCustomMovementComponent, GroundTraceDistance), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_GroundTraceDistance_MetaData), Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_GroundTraceDistance_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ObstacleTraceDistance_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Character Movement: Flying" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xc5\xb8\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Public/Components/CustomMovementComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xc5\xb8\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ObstacleTraceDistance = { "ObstacleTraceDistance", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCustomMovementComponent, ObstacleTraceDistance), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ObstacleTraceDistance_MetaData), Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ObstacleTraceDistance_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCustomMovementComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbableSurfaceTraceTypes_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbableSurfaceTraceTypes,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbCapsuleTraceRadius,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbCapsuleTraceHalfHeight,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_SwimTraceRadius,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_SwimTraceDepth,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_FlightTraceDistance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_CeilingTraceDistance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_GroundTraceDistance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ObstacleTraceDistance,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCustomMovementComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCustomMovementComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UCustomMovementComponent_Statics::ClassParams = {
		&UCustomMovementComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UCustomMovementComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UCustomMovementComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomMovementComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UCustomMovementComponent_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomMovementComponent_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UCustomMovementComponent()
	{
		if (!Z_Registration_Info_UClass_UCustomMovementComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCustomMovementComponent.OuterSingleton, Z_Construct_UClass_UCustomMovementComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UCustomMovementComponent.OuterSingleton;
	}
	template<> WARRIOR_API UClass* StaticClass<UCustomMovementComponent>()
	{
		return UCustomMovementComponent::StaticClass();
	}
	UCustomMovementComponent::UCustomMovementComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCustomMovementComponent);
	UCustomMovementComponent::~UCustomMovementComponent() {}
	struct Z_CompiledInDeferFile_FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UCustomMovementComponent, UCustomMovementComponent::StaticClass, TEXT("UCustomMovementComponent"), &Z_Registration_Info_UClass_UCustomMovementComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCustomMovementComponent), 847684006U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h_3971030037(TEXT("/Script/Warrior"),
		Z_CompiledInDeferFile_FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
