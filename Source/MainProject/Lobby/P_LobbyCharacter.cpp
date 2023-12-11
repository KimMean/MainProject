#include "Lobby/P_LobbyCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"


AP_LobbyCharacter::AP_LobbyCharacter()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	//SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	//Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	RootComponent = CapsuleComponent;
	SkeletalMesh->SetupAttachment(RootComponent);
	//SpringArm->SetupAttachment(RootComponent);
	//Camera->SetupAttachment(SpringArm);

	CapsuleComponent->SetCapsuleHalfHeight(88.0f);
	CapsuleComponent->SetCapsuleRadius(34.0f);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/Characters/TwinBlast/Meshes/TwinBlast_ShadowOps.TwinBlast_ShadowOps'");
	SkeletalMesh->SetSkeletalMesh(mesh.Object);
	SkeletalMesh->SetRelativeLocation(FVector(0, 0, -90));
	SkeletalMesh->SetRelativeRotation(FRotator(0, -90, 0));
}

void AP_LobbyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


