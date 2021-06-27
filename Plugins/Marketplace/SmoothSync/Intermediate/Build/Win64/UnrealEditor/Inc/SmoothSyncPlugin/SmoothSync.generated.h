// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FVector;
class USceneComponent;
#ifdef SMOOTHSYNCPLUGIN_SmoothSync_generated_h
#error "SmoothSync.generated.h already included, missing '#pragma once' in SmoothSync.h"
#endif
#define SMOOTHSYNCPLUGIN_SmoothSync_generated_h

#define GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_SPARSE_DATA
#define GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_RPC_WRAPPERS \
	virtual bool SmoothSyncTeleportClientToServer_Validate(FVector , FVector , FVector , float ); \
	virtual void SmoothSyncTeleportClientToServer_Implementation(FVector position, FVector rotation, FVector scale, float tempOwnerTime); \
	virtual bool SmoothSyncTeleportServerToClients_Validate(FVector , FVector , FVector , float ); \
	virtual void SmoothSyncTeleportServerToClients_Implementation(FVector position, FVector rotation, FVector scale, float tempOwnerTime); \
	virtual bool SmoothSyncEnableClientToServer_Validate(bool ); \
	virtual void SmoothSyncEnableClientToServer_Implementation(bool enable); \
	virtual bool SmoothSyncEnableServerToClients_Validate(bool ); \
	virtual void SmoothSyncEnableServerToClients_Implementation(bool enable); \
	virtual bool ClientSendsTransformToServer_Validate(TArray<uint8> const& ); \
	virtual void ClientSendsTransformToServer_Implementation(TArray<uint8> const& value); \
	virtual bool ServerSendsTransformToEveryone_Validate(TArray<uint8> const& ); \
	virtual void ServerSendsTransformToEveryone_Implementation(TArray<uint8> const& value); \
 \
	DECLARE_FUNCTION(execSmoothSyncTeleportClientToServer); \
	DECLARE_FUNCTION(execSmoothSyncTeleportServerToClients); \
	DECLARE_FUNCTION(execSmoothSyncEnableClientToServer); \
	DECLARE_FUNCTION(execSmoothSyncEnableServerToClients); \
	DECLARE_FUNCTION(execClientSendsTransformToServer); \
	DECLARE_FUNCTION(execServerSendsTransformToEveryone); \
	DECLARE_FUNCTION(execsetSceneComponentToSync); \
	DECLARE_FUNCTION(execforceStateSendNextFrame); \
	DECLARE_FUNCTION(execenableSmoothSync); \
	DECLARE_FUNCTION(execteleport); \
	DECLARE_FUNCTION(execclearBuffer);


#define GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual bool SmoothSyncTeleportClientToServer_Validate(FVector , FVector , FVector , float ); \
	virtual void SmoothSyncTeleportClientToServer_Implementation(FVector position, FVector rotation, FVector scale, float tempOwnerTime); \
	virtual bool SmoothSyncTeleportServerToClients_Validate(FVector , FVector , FVector , float ); \
	virtual void SmoothSyncTeleportServerToClients_Implementation(FVector position, FVector rotation, FVector scale, float tempOwnerTime); \
	virtual bool SmoothSyncEnableClientToServer_Validate(bool ); \
	virtual void SmoothSyncEnableClientToServer_Implementation(bool enable); \
	virtual bool SmoothSyncEnableServerToClients_Validate(bool ); \
	virtual void SmoothSyncEnableServerToClients_Implementation(bool enable); \
	virtual bool ClientSendsTransformToServer_Validate(TArray<uint8> const& ); \
	virtual void ClientSendsTransformToServer_Implementation(TArray<uint8> const& value); \
	virtual bool ServerSendsTransformToEveryone_Validate(TArray<uint8> const& ); \
	virtual void ServerSendsTransformToEveryone_Implementation(TArray<uint8> const& value); \
 \
	DECLARE_FUNCTION(execSmoothSyncTeleportClientToServer); \
	DECLARE_FUNCTION(execSmoothSyncTeleportServerToClients); \
	DECLARE_FUNCTION(execSmoothSyncEnableClientToServer); \
	DECLARE_FUNCTION(execSmoothSyncEnableServerToClients); \
	DECLARE_FUNCTION(execClientSendsTransformToServer); \
	DECLARE_FUNCTION(execServerSendsTransformToEveryone); \
	DECLARE_FUNCTION(execsetSceneComponentToSync); \
	DECLARE_FUNCTION(execforceStateSendNextFrame); \
	DECLARE_FUNCTION(execenableSmoothSync); \
	DECLARE_FUNCTION(execteleport); \
	DECLARE_FUNCTION(execclearBuffer);


#define GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_EVENT_PARMS \
	struct SmoothSync_eventClientSendsTransformToServer_Parms \
	{ \
		TArray<uint8> value; \
	}; \
	struct SmoothSync_eventServerSendsTransformToEveryone_Parms \
	{ \
		TArray<uint8> value; \
	}; \
	struct SmoothSync_eventSmoothSyncEnableClientToServer_Parms \
	{ \
		bool enable; \
	}; \
	struct SmoothSync_eventSmoothSyncEnableServerToClients_Parms \
	{ \
		bool enable; \
	}; \
	struct SmoothSync_eventSmoothSyncTeleportClientToServer_Parms \
	{ \
		FVector position; \
		FVector rotation; \
		FVector scale; \
		float tempOwnerTime; \
	}; \
	struct SmoothSync_eventSmoothSyncTeleportServerToClients_Parms \
	{ \
		FVector position; \
		FVector rotation; \
		FVector scale; \
		float tempOwnerTime; \
	};


#define GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_CALLBACK_WRAPPERS
#define GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSmoothSync(); \
	friend struct Z_Construct_UClass_USmoothSync_Statics; \
public: \
	DECLARE_CLASS(USmoothSync, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SmoothSyncPlugin"), NO_API) \
	DECLARE_SERIALIZER(USmoothSync)


#define GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_INCLASS \
private: \
	static void StaticRegisterNativesUSmoothSync(); \
	friend struct Z_Construct_UClass_USmoothSync_Statics; \
public: \
	DECLARE_CLASS(USmoothSync, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SmoothSyncPlugin"), NO_API) \
	DECLARE_SERIALIZER(USmoothSync)


#define GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USmoothSync(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USmoothSync) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USmoothSync); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USmoothSync); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USmoothSync(USmoothSync&&); \
	NO_API USmoothSync(const USmoothSync&); \
public:


#define GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USmoothSync(USmoothSync&&); \
	NO_API USmoothSync(const USmoothSync&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USmoothSync); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USmoothSync); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(USmoothSync)


#define GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_PRIVATE_PROPERTY_OFFSET
#define GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_41_PROLOG \
	GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_EVENT_PARMS


#define GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_PRIVATE_PROPERTY_OFFSET \
	GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_SPARSE_DATA \
	GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_RPC_WRAPPERS \
	GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_CALLBACK_WRAPPERS \
	GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_INCLASS \
	GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_PRIVATE_PROPERTY_OFFSET \
	GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_SPARSE_DATA \
	GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_RPC_WRAPPERS_NO_PURE_DECLS \
	GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_CALLBACK_WRAPPERS \
	GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_INCLASS_NO_PURE_DECLS \
	GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h_44_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SMOOTHSYNCPLUGIN_API UClass* StaticClass<class USmoothSync>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID GolfBR_Plugins_Marketplace_SmoothSync_Source_SmoothSyncPlugin_Public_SmoothSync_h


#define FOREACH_ENUM_RESTSTATE(op) \
	op(RestState::AT_REST) \
	op(RestState::JUST_STARTED_MOVING) \
	op(RestState::MOVING) 

enum class RestState : uint8;
template<> SMOOTHSYNCPLUGIN_API UEnum* StaticEnum<RestState>();

#define FOREACH_ENUM_EXTRAPOLATIONMODE(op) \
	op(ExtrapolationMode::UNLIMITED) \
	op(ExtrapolationMode::LIMITED) \
	op(ExtrapolationMode::NONE) 

enum class ExtrapolationMode : uint8;
template<> SMOOTHSYNCPLUGIN_API UEnum* StaticEnum<ExtrapolationMode>();

#define FOREACH_ENUM_SYNCMODE(op) \
	op(SyncMode::XYZ) \
	op(SyncMode::XY) \
	op(SyncMode::XZ) \
	op(SyncMode::YZ) \
	op(SyncMode::X) \
	op(SyncMode::Y) \
	op(SyncMode::Z) \
	op(SyncMode::NONE) 

enum class SyncMode : uint8;
template<> SMOOTHSYNCPLUGIN_API UEnum* StaticEnum<SyncMode>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
