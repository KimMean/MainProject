#include "Character/DefaultCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ADefaultCharacter::ADefaultCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 500.0f;
	SpringArm->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void ADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

