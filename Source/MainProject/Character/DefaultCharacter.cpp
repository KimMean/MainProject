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

void ADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADefaultCharacter::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADefaultCharacter::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ADefaultCharacter::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ADefaultCharacter::OnVerticalLook);
}

void ADefaultCharacter::OnMoveForward(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void ADefaultCharacter::OnMoveRight(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void ADefaultCharacter::OnHorizontalLook(float Axis)
{
	AddControllerYawInput(Axis);
}

void ADefaultCharacter::OnVerticalLook(float Axis)
{
	AddControllerPitchInput(Axis);
}

