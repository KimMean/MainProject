#include "Character/Character_TwinBlast.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

ACharacter_TwinBlast::ACharacter_TwinBlast()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 500.0f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetRelativeLocation(FVector(0, 30, 90));

	GetCharacterMovement()->MaxWalkSpeed = JogSpeed;

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

void ACharacter_TwinBlast::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacter_TwinBlast::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacter_TwinBlast::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACharacter_TwinBlast::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACharacter_TwinBlast::OnVerticalLook);

	PlayerInputComponent->BindAction("Walk", EInputEvent::IE_Pressed, this, &ACharacter_TwinBlast::OnWalkMode);
	PlayerInputComponent->BindAction("Walk", EInputEvent::IE_Released, this, &ACharacter_TwinBlast::OnJogMode);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ACharacter_TwinBlast::OnSprintMode);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACharacter_TwinBlast::OnJogMode);
}

void ACharacter_TwinBlast::OnMoveForward(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void ACharacter_TwinBlast::OnMoveRight(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void ACharacter_TwinBlast::OnHorizontalLook(float Axis)
{
	AddControllerYawInput(Axis);
}

void ACharacter_TwinBlast::OnVerticalLook(float Axis)
{
	AddControllerPitchInput(Axis);
}

void ACharacter_TwinBlast::OnWalkMode()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ACharacter_TwinBlast::OnJogMode()
{
	GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
}

void ACharacter_TwinBlast::OnSprintMode()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}
