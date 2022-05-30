// Copyright Epic Games, Inc. All Rights Reserved.

#include "MineSweeperBlock.h"
#include "MineSweeperBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include "api/Context.h"

AMineSweeperBlock::AMineSweeperBlock()
{
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> MineBackColorMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> FloorColorMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> HighlightColorMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> MS_0_Material;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> MS_1_Material;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> MS_2_Material;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> MS_3_Material;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> MS_4_Material;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> MS_5_Material;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> MS_6_Material;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> MS_7_Material;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> MS_8_Material;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> MS_Bomb_Material;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> MS_Flag_Material;


		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/MineSweeper/Meshes/PuzzleCube.PuzzleCube"))
			, BaseMaterial(TEXT("/Game/MineSweeper/Meshes/BaseMaterial.BaseMaterial"))
			, MineBackColorMaterial(TEXT("/Game/MineSweeper/Meshes/MineMaterial.MineMaterial"))
			, HighlightColorMaterial(TEXT("/Game/MineSweeper/Meshes/MS-00_Mat_Inst.MS-00_Mat_Inst"))
			, FloorColorMaterial(TEXT("/Game/MineSweeper/Meshes/MS-00_Mat_Inst.MS-00_Mat_Inst"))
			, MS_0_Material(TEXT("/Game/MineSweeper/Meshes/MS-00_Mat_Inst.MS-00_Mat_Inst"))
			, MS_1_Material(TEXT("/Game/MineSweeper/Meshes/MS-01_Mat_Inst.MS-01_Mat_Inst"))
			, MS_2_Material(TEXT("/Game/MineSweeper/Meshes/MS-02_Mat_Inst.MS-02_Mat_Inst"))
			, MS_3_Material(TEXT("/Game/MineSweeper/Meshes/MS-03_Mat_Inst.MS-03_Mat_Inst"))
			, MS_4_Material(TEXT("/Game/MineSweeper/Meshes/MS-04_Mat_Inst.MS-04_Mat_Inst"))
			, MS_5_Material(TEXT("/Game/MineSweeper/Meshes/MS-05_Mat_Inst.MS-05_Mat_Inst"))
			, MS_6_Material(TEXT("/Game/MineSweeper/Meshes/MS-06_Mat_Inst.MS-06_Mat_Inst"))
			, MS_7_Material(TEXT("/Game/MineSweeper/Meshes/MS-07_Mat_Inst.MS-07_Mat_Inst"))
			, MS_8_Material(TEXT("/Game/MineSweeper/Meshes/MS-08_Mat_Inst.MS-08_Mat_Inst"))
			, MS_Bomb_Material(TEXT("/Game/MineSweeper/Meshes/MS-Bomb_Mat_Inst.MS-Bomb_Mat_Inst"))
			, MS_Flag_Material(TEXT("/Game/MineSweeper/Meshes/MS-Flag_Mat_Inst.MS-Flag_Mat_Inst"))
		{
		}
	};

	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f,1.f,0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f,0.f,25.f));
	BlockMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	BlockMesh->SetMaterial(0, ConstructorStatics.MineBackColorMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &AMineSweeperBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &AMineSweeperBlock::OnFingerPressedBlock);

	// Save a pointer to the orange material
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	MineBackColorMaterial = ConstructorStatics.MineBackColorMaterial.Get();
	FloorColorMaterial = ConstructorStatics.FloorColorMaterial.Get();
	HighlightColorMaterial = ConstructorStatics.HighlightColorMaterial.Get();

	MS_0_Material = ConstructorStatics.MS_0_Material.Get();
	MS_1_Material = ConstructorStatics.MS_1_Material.Get();
	MS_2_Material = ConstructorStatics.MS_2_Material.Get();
	MS_3_Material = ConstructorStatics.MS_3_Material.Get();
	MS_4_Material = ConstructorStatics.MS_4_Material.Get();
	MS_5_Material = ConstructorStatics.MS_5_Material.Get();
	MS_6_Material = ConstructorStatics.MS_6_Material.Get();
	MS_7_Material = ConstructorStatics.MS_7_Material.Get();
	MS_8_Material = ConstructorStatics.MS_8_Material.Get();
	MS_Bomb_Material = ConstructorStatics.MS_Bomb_Material.Get();
	MS_Flag_Material = ConstructorStatics.MS_Flag_Material.Get();
}

void AMineSweeperBlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}

void AMineSweeperBlock::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	HandleClicked();
}

void AMineSweeperBlock::HandleClicked()
{	
	if (HasOpened)
	{
		return;
	}

	Context::GetContext().OpenCell(CellPosition->X, CellPosition->Y);		
}

void AMineSweeperBlock::Highlight(bool bOn)
{
	if (bIsActive || HasOpened || HasFlaged)
	{
		return;
	}

	if (bOn)
	{
		BlockMesh->SetMaterial(0, BaseMaterial);
	}
	else
	{
		BlockMesh->SetMaterial(0, MineBackColorMaterial);
	}
}

void AMineSweeperBlock::FlagMine()
{
	if (HasOpened)
	{
		return;
	}
	if (HasFlaged)
	{
		BlockMesh->SetMaterial(0, BaseMaterial);
		HasFlaged = false;
	}
	else
	{
		HasFlaged = true;
		BlockMesh->SetMaterial(0, MS_Flag_Material);
	}	
}

void AMineSweeperBlock::UpdateBlock(EBlockStates state)
{
	switch(state)
	{
		case EBlockStates::Zero:
			BlockMesh->SetMaterial(0, MS_0_Material);
			HasOpened = true;
			break;
		case EBlockStates::One:
			BlockMesh->SetMaterial(0, MS_1_Material);
			HasOpened = true;
			break;
		case EBlockStates::Two:
			BlockMesh->SetMaterial(0, MS_2_Material);
			HasOpened = true;
			break;
		case EBlockStates::Three:
			BlockMesh->SetMaterial(0, MS_3_Material);
			HasOpened = true;
			break;
		case EBlockStates::Four:
			BlockMesh->SetMaterial(0, MS_4_Material);
			HasOpened = true;
			break;
		case EBlockStates::Five:
			BlockMesh->SetMaterial(0, MS_5_Material);
			HasOpened = true;
			break;
		case EBlockStates::Six:
			BlockMesh->SetMaterial(0, MS_6_Material);
			HasOpened = true;
			break;
		case EBlockStates::Seven:
			BlockMesh->SetMaterial(0, MS_7_Material);
			HasOpened = true;
			break;
		case EBlockStates::Eight:
			BlockMesh->SetMaterial(0, MS_8_Material);
			HasOpened = true;
			break;
		case EBlockStates::Explode:
			BlockMesh->SetMaterial(0, MS_Bomb_Material);
			HasOpened = true;
			break;
		case EBlockStates::Flag:
			BlockMesh->SetMaterial(0, MS_Flag_Material);
			HasOpened = true;
			break;
	}
}

void AMineSweeperBlock::OnOpeningCell(const FString msg)
{
	HasOpened = true;	
}
