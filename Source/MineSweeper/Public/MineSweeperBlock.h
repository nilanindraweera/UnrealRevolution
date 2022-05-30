// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <memory>
#include <api/Types.h>
#include "MineSweeperBlock.generated.h"

/** A block that can be clicked */
UCLASS(minimalapi)
class AMineSweeperBlock : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;

public:
	AMineSweeperBlock();

	/** Are we currently active? */
	bool bIsActive;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		bool HasOpened = false;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		bool HasFlaged = false;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		bool HasExploded = false;

	/** Pointer to white material used on the focused block */
	UPROPERTY()
	class UMaterial* BaseMaterial;

	UPROPERTY()
		class UMaterialInstance* HighlightColorMaterial;

	UPROPERTY()
		class UMaterialInstance* FloorColorMaterial;

	UPROPERTY()
		class UMaterialInstance* MineBackColorMaterial;

	UPROPERTY()
		class UMaterialInstance* MS_0_Material;

	UPROPERTY()
		class UMaterialInstance* MS_1_Material;

	UPROPERTY()
		class UMaterialInstance* MS_2_Material;

	UPROPERTY()
		class UMaterialInstance* MS_3_Material;

	UPROPERTY()
		class UMaterialInstance* MS_4_Material;

	UPROPERTY()
		class UMaterialInstance* MS_5_Material;

	UPROPERTY()
		class UMaterialInstance* MS_6_Material;

	UPROPERTY()
		class UMaterialInstance* MS_7_Material;

	UPROPERTY()
		class UMaterialInstance* MS_8_Material;

	UPROPERTY()
		class UMaterialInstance* MS_Bomb_Material;

	UPROPERTY()
		class UMaterialInstance* MS_Flag_Material;


	UPROPERTY()
	class AMineSweeperBlockGrid* OwningGrid;

	/** Handle the block being clicked */
	UFUNCTION()
	void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	/** Handle the block being touched  */
	UFUNCTION()
	void OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	void HandleClicked();

	void Highlight(bool bOn);

	void FlagMine();

	void UpdateBlock(EBlockStates state);

private:
	void OnOpeningCell(const FString msg);

private:
	FDelegateHandle m_onOpeningCellDelegateHandle;

public:
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }

public:
	std::shared_ptr<FCellPosition> CellPosition = nullptr;
};
