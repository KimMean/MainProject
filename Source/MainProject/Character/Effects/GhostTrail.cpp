#include "Character/Effects/GhostTrail.h"

#include "Engine/SkeletalMesh.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Components/PoseableMeshComponent.h"

AGhostTrail::AGhostTrail()
{
	PrimaryActorTick.bCanEverTick = true;

	PoseableMesh = CreateDefaultSubobject < UPoseableMeshComponent>(TEXT("PoseableMesh"));

	RootComponent = PoseableMesh;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> poseMesh(TEXT("SkeletalMesh'/Game/Characters/TwinBlast/Meshes/TwinBlast_ShadowOps.TwinBlast_ShadowOps'"));
	PoseableMesh->SetSkeletalMesh(poseMesh.Object);

	ConstructorHelpers::FObjectFinder<UMaterialInstance> ghostMat(TEXT("MaterialInstanceConstant'/Game/Characters/TwinBlast/Materials/M_GhostTrail_Inst.M_GhostTrail_Inst'"));
	GhostMaterial = ghostMat.Object;
}

void AGhostTrail::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGhostTrail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsSpawned)
	{
		FadeCountDown -= DeltaTime;
		for (int i = 0; i < Materials.Num(); i++)
		{
			Materials[i]->SetScalarParameterValue("Opacity", FadeCountDown / FadeOutTime);
		}
		if (FadeCountDown < 0)
		{
			Destroy();
		}
	}

}

void AGhostTrail::SetSkeletalMeshPose(USkeletalMeshComponent* InSkeletalMesh)
{
	PoseableMesh->CopyPoseFromSkeletalComponent(InSkeletalMesh);

	TArray<UMaterialInterface*> materials = PoseableMesh->GetMaterials();

	for (int32 i = 0; i < materials.Num(); i++)
	{
		Materials.Add(UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), GhostMaterial));
		PoseableMesh->SetMaterial(i, Materials[i]);
	}

	FadeCountDown = FadeOutTime;
	IsSpawned = true;
}




