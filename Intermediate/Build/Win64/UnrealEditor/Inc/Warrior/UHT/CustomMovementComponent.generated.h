// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Components/CustomMovementComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef WARRIOR_CustomMovementComponent_generated_h
#error "CustomMovementComponent.generated.h already included, missing '#pragma once' in CustomMovementComponent.h"
#endif
#define WARRIOR_CustomMovementComponent_generated_h

#define FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h_16_SPARSE_DATA
#define FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h_16_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h_16_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execCheckObstacleAhead); \
	DECLARE_FUNCTION(execIsGroundBelow); \
	DECLARE_FUNCTION(execIsCeilingAbove); \
	DECLARE_FUNCTION(execCheckFlightCondition); \
	DECLARE_FUNCTION(execCheckSwimmingCondition);


#define FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h_16_ACCESSORS
#define FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCustomMovementComponent(); \
	friend struct Z_Construct_UClass_UCustomMovementComponent_Statics; \
public: \
	DECLARE_CLASS(UCustomMovementComponent, UCharacterMovementComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Warrior"), NO_API) \
	DECLARE_SERIALIZER(UCustomMovementComponent)


#define FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h_16_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCustomMovementComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCustomMovementComponent(UCustomMovementComponent&&); \
	NO_API UCustomMovementComponent(const UCustomMovementComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCustomMovementComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCustomMovementComponent); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCustomMovementComponent) \
	NO_API virtual ~UCustomMovementComponent();


#define FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h_13_PROLOG
#define FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h_16_SPARSE_DATA \
	FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h_16_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h_16_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h_16_ACCESSORS \
	FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h_16_INCLASS_NO_PURE_DECLS \
	FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> WARRIOR_API UClass* StaticClass<class UCustomMovementComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_02_Warrior_Source_Warrior_Public_Components_CustomMovementComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
