//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
//#include "SimCommonTypes.h"
//#include "BlueprintTypes.generated.h"
//
//USTRUCT(BlueprintType)
//struct FSimCPMPositionProperty
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(BlueprintReadWrite, Category = "Position")
//		float X;
//	UPROPERTY(BlueprintReadWrite, Category = "Position")
//		float Y;
//	UPROPERTY(BlueprintReadWrite, Category = "Position")
//		float Z;
//};
//
//USTRUCT(BlueprintType)
//struct FSimCPMOrientationProperty
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(BlueprintReadWrite, Category = "Orientation")
//		float Roll; //X
//	UPROPERTY(BlueprintReadWrite, Category = "Orientation")
//		float Pitch; //Y
//	UPROPERTY(BlueprintReadWrite, Category = "Orientation")
//		float Yaw; //Z
//};
//
//USTRUCT(BlueprintType)
//struct FSimCPMVelocityProperty
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(BlueprintReadWrite, Category = "Velocity")
//		float X;
//	UPROPERTY(BlueprintReadWrite, Category = "Velocity")
//		float Y;
//	UPROPERTY(BlueprintReadWrite, Category = "Velocity")
//		float Z;
//};
//
//USTRUCT(BlueprintType)
//struct FSimCPMEntityStateProperty
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(BlueprintReadWrite, Category = "Entity State")
//		FString Marking;
//};
//
//USTRUCT(BlueprintType)
//struct FSimCPMArticulatedPart
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(BlueprintReadWrite, Category = "Articulated Part")
//		TEnumAsByte<ESimArticulatePart> ArticulatePart;
//	UPROPERTY(BlueprintReadWrite, Category = "Articulated Part")
//		TEnumAsByte<ESimArticulateTransform> ArticulateTransform;
//	UPROPERTY(BlueprintReadWrite, Category = "Articulated Part")
//		float Value;
//};
//
//UENUM(BlueprintType)
//enum SimCPMEntityType
//{
//	HUMAN_DIS_ENTITY,
//	VEHICLE_DIS_ENTITY,
//	AIRCRAFT_DIS_ENTITY,
//	MUNITION_DIS_ENTITY
//};
//
//UENUM(BlueprintType)
//enum PodActionType
//{
//	SHOW_CAMERA,
//	UPDATE_CAMERA,
//	HIDE_CAMERA
//};
//
//UENUM(BlueprintType)
//enum RestMessageType
//{
//	INVALID_MESSAGE,
//	FEATURE_COLLECTION_CREATE,
//	FEATURE_COLLECTION_REMOVE,
//	SESSION_START,
//	SESSION_END
//};
//
//UENUM(BlueprintType)
//enum FeatureGeometryType
//{
//	GEOMETRY_NONE,
//	LINE_STRING_GEOMETRY,
//	POLYGON_GEOMETRY
//};
//
//USTRUCT(BlueprintType)
//struct FGeometryFeature
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_GeometryFeature")
//		TEnumAsByte<FeatureGeometryType> GeometryType;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_GeometryFeature")
//		TArray<FSimCPMPositionProperty> CoordinatesArray;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_GeometryFeature")
//		FLinearColor Color;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_GeometryFeature")
//		float LineWidth;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_GeometryFeature")
//		float Height;
//};
//
////USTRUCT(BlueprintType)
////struct FCString
////{
////	GENERATED_BODY()
////public:
////	const wchar_t* str;
////	unsigned int size;
////};
//
//USTRUCT(BlueprintType)
//struct FSimCPMEntityCreationData
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_EntityCreationData")
//		int32 Id;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_EntityCreationData")
//		FSimCPMPositionProperty Position;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_EntityCreationData")
//		FSimCPMOrientationProperty Orientation;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_EntityCreationData")
//		FSimCPMVelocityProperty Velocity;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_EntityCreationData")
//		FSimCPMEntityStateProperty EntityState;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_EntityCreationData")
//		TArray<FSimCPMArticulatedPart> ArticulatedParts;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_EntityCreationData")
//		TEnumAsByte<SimCPMEntityType> EntityType;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_EntityCreationData")
//		FString EntityModelName;
//};
//
//USTRUCT(BlueprintType)
//struct FSimCPMEntityModifiedData
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_EntityModificationData")
//		int32 Id;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_EntityModificationData")
//		FSimCPMPositionProperty Position;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_EntityModificationData")
//		FSimCPMOrientationProperty Orientation;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_EntityModificationData")
//		FSimCPMVelocityProperty Velocity;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_EntityModificationData")
//		TArray<FSimCPMArticulatedPart> ArticulatedParts;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_EntityModificationData")
//		TEnumAsByte<SimCPMEntityType> EntityType;
//};
//
//USTRUCT(BlueprintType)
//struct FSimCPMEntityDeletionData
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_EntityDeletionData")
//		int32 Id;
//};
//
//USTRUCT(BlueprintType)
//struct FSimCPMFireCreationData
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_FireCreationData")
//		int32 Id;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_FireCreationData")
//		FSimCPMPositionProperty Position;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_FireCreationData")
//		FSimCPMOrientationProperty Orientation;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_FireCreationData")
//		FSimCPMVelocityProperty Velocity;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_FireCreationData")
//		int32 FiringEntityId;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_FireCreationData")
//		FString FuseType;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_FireCreationData")
//		FString AmmunitionType;
//};
//
//USTRUCT(BlueprintType)
//struct FSimCPMDetonationData
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_DetonationCreationData")
//		int32 Id;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_DetonationCreationData")
//		int32 MunitionId;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_DetonationCreationData")
//		FSimCPMPositionProperty Position;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_DetonationCreationData")
//		int32 FiringEntityId;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_DetonationCreationData")
//		FString FuseType;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_DetonationCreationData")
//		FString AmmunitionType;
//};
//
//USTRUCT(BlueprintType)
//struct FSimCPMDesignatorData
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_DesignatorData")
//		int32 Id;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_DesignatorData")
//		int32 OriginatingEntityId;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_DesignatorData")
//		int32 DesignatedEntityId;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_DesignatorData")
//		bool RemoteDesignatedEntity;
//	UPROPERTY(BlueprintReadOnly, Category = "DIS_DesignatorData") // BlueprintReadOnly
//		AActor* DesignatedActor;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_DesignatorData")
//		FSimCPMPositionProperty DesignatorSpotLocation;	
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_DesignatorData")
//		int32 DesignatorCode;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_DesignatorData")
//		float EmissionWavelength;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_DesignatorData")
//		float DesignatorPower;
//};
//
//USTRUCT(BlueprintType)
//struct FSimCPMDesignatorDeletionData
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_DesignatorDeletionData")
//		int32 Id;
//};
//
//USTRUCT(BlueprintType)
//struct FSimCPMPodActionData
//{
//	GENERATED_BODY()
//
//public:
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_PodActionData")
//		int32 PodId;
//
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_PodActionData")
//		TEnumAsByte<PodActionType> PodActionType;
//};
//
//USTRUCT(BlueprintType)
//struct FSimCPMRestMessageData
//{
//	GENERATED_BODY()
//
//public:
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_RestMessageData")
//		int32 UUID;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_RestMessageData")
//		TEnumAsByte<RestMessageType> MessageType;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_RestMessageData")
//		TArray<FGeometryFeature> GeometryFeatures;
//};
//
//USTRUCT(BlueprintType)
//struct FSimCPMEntityMappingData
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_EntityMappingData")
//		FString EntityName;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_EntityMappingData")
//		FString OutgoingMapping;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_EntityMappingData")
//		FString IncomingMapping;
//};
//
//USTRUCT(BlueprintType)
//struct FSimCPMEntityMappingList
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_EntityMappingList")
//		TArray<FSimCPMEntityMappingData> EntityMappingArray;
//};
//
//USTRUCT(BlueprintType)
//struct FSimCPMApplicationSettingsData
//{
//	GENERATED_BODY()
//public:
//	// DIS Settings
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_ApplicationSettingsData")
//		FString SendAddress;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_ApplicationSettingsData")
//		FString ReceiveAddress;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_ApplicationSettingsData")
//		int32 ExerciseID;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_ApplicationSettingsData")
//		int32 ApplicationID;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_ApplicationSettingsData")
//		int32 SiteID;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_ApplicationSettingsData")
//		int32 SendPort;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_ApplicationSettingsData")
//		int32 ReceivePort;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_ApplicationSettingsData")
//		int32 Heartbeat;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_ApplicationSettingsData")
//		int32 DISVersion;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_ApplicationSettingsData")
//		int32 DeleteTimeout;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_ApplicationSettingsData")
//		int32 UseNetworkByteOrder;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_ApplicationSettingsData")
//		int32 DeadReckoning;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_ApplicationSettingsData")
//		int32 DRPositionThreshold;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_ApplicationSettingsData")
//		int32 DRRotationThreshold;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_ApplicationSettingsData")
//		int32 DRTimeThreshold;
//
//	// HLA Settings
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_ApplicationSettingsData")
//		FString CrcAddress;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_ApplicationSettingsData")
//		int32 CrcPort;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_ApplicationSettingsData")
//		FString FederateName;
//	UPROPERTY(BlueprintReadWrite, Category = "DIS_ApplicationSettingsData")
//		FString FederationName;
//};
//
//
//
//
////UCLASS()
////class UNREALSIMDIS_API UBlueprintTypes : public UObject
////{
////	GENERATED_BODY()
////	
////};
