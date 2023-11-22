#include "Character/Character_TwinBlast.h"

ACharacter_TwinBlast::ACharacter_TwinBlast()
{
	PrimaryActorTick.bCanEverTick = true;


	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/Characters/TwinBlast/Meshes/TwinBlast_ShadowOps.TwinBlast_ShadowOps'");
	verifyf(mesh.Succeeded(), L"mesh.succeeded()");
	GetMesh()->SetSkeletalMesh(mesh.Object);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
}

void ACharacter_TwinBlast::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacter_TwinBlast::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
