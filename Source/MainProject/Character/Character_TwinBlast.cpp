#include "Character/Character_TwinBlast.h"

#include "Engine/SkeletalMeshSocket.h"

#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"

#include "Character/Components/AnimationComponent.h"
#include "Character/Components/StatusComponent.h"
#include "Character/Widgets/MainWidget.h"
#include "Character/Bullets/Bullet.h"
#include "Utilities/DebugLog.h"

ACharacter_TwinBlast::ACharacter_TwinBlast()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	Animation = CreateDefaultSubobject<UAnimationComponent>(TEXT("Animation"));
	Status = CreateDefaultSubobject<UStatusComponent>(TEXT("Status"));
	State = CreateDefaultSubobject<UStateComponent>(TEXT("State"));


	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
	//Status->SetupAttachment(RootComponent);

	SpringArm->TargetArmLength = Status->GetBaseArmLength();
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetRelativeLocation(FVector(0, 30, 90));

	bUseControllerRotationYaw = true;
	//GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = Status->GetRunSpeed();

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/Characters/TwinBlast/Meshes/TwinBlast_ShadowOps.TwinBlast_ShadowOps'");
	verifyf(mesh.Succeeded(), L"mesh.succeeded()");
	GetMesh()->SetSkeletalMesh(mesh.Object);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	ConstructorHelpers::FClassFinder<UMainWidget> widget(L"WidgetBlueprint'/Game/Characters/TwinBlast/Widgets/WBP_MainWidget.WBP_MainWidget_C'");
	MainWidgetClass = widget.Class;
	
	ConstructorHelpers::FClassFinder<ABullet> bullet(L"Blueprint'/Game/Characters/TwinBlast/Bullets/BP_Bullet.BP_Bullet_C'");
	Bullet = bullet.Class;
}

void ACharacter_TwinBlast::BeginPlay()
{
	Super::BeginPlay();

	MainWidget = CreateWidget<UMainWidget, APlayerController>(GetController<APlayerController>(), MainWidgetClass);
	MainWidget->AddToViewport();
	MainWidget->Set_WBP_HPBar_Percent(0.5f);

	State->OnStateTypeChanged.AddDynamic(this, &ACharacter_TwinBlast::OnStateTypeChanged);
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

	//PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter_TwinBlast::OnJump);
	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &ACharacter_TwinBlast::OnAttack);
	PlayerInputComponent->BindAction("Walk", EInputEvent::IE_Pressed, this, &ACharacter_TwinBlast::OnWalkMode);
	PlayerInputComponent->BindAction("Walk", EInputEvent::IE_Released, this, &ACharacter_TwinBlast::OnJogMode);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ACharacter_TwinBlast::OnSprintMode);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACharacter_TwinBlast::OnJogMode);
	//PlayerInputComponent->BindAction("Avoid", EInputEvent::IE_Pressed, this, &ACharacter_TwinBlast::OnAvoid);

	PlayerInputComponent->BindAction("AimMode", EInputEvent::IE_Pressed, this, &ACharacter_TwinBlast::OnAimMode);
	PlayerInputComponent->BindAction("AimMode", EInputEvent::IE_Released, this, &ACharacter_TwinBlast::OffAimMode);
}

void ACharacter_TwinBlast::Begin_DoubleCombo()
{
	if (!Status->GetComboAttack())
		return;

	DebugLog::Print("Begin_DoubleCombo");
	Animation->Attack_DoubleShotCombo();
}

void ACharacter_TwinBlast::End_DoubleShot()
{
	DebugLog::Print("End_DoubleShot");
	Status->SetComboAttack(false);
	Status->SetAttack(false);
}

void ACharacter_TwinBlast::BulletFiring(const USkeletalMeshSocket* socket)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector location = GetMesh()->GetSocketLocation(socket->SocketName);
	FRotator rotator;
	ABullet* bullet = GetWorld()->SpawnActor<ABullet>(Bullet, location, rotator, SpawnParams);
	if (bullet == nullptr)
	{
		DebugLog::Print("Error");
		return;
	}
	bullet->SetDirection(Camera->GetForwardVector());
}

void ACharacter_TwinBlast::OnMoveForward(float Axis)
{
	//FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	//FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();
	FVector direction = UKismetMathLibrary::GetForwardVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));
	AddMovementInput(direction, Axis);
}

void ACharacter_TwinBlast::OnMoveRight(float Axis)
{
	//FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	//FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();
	FVector direction = UKismetMathLibrary::GetRightVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));
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

void ACharacter_TwinBlast::OnJump()
{
	//if (Status->GetInAir())
	//	return;
	//Status->SetInAir(GetMovementComponent()->IsFalling());
}

void ACharacter_TwinBlast::OnAttack()
{
	if (!Status->GetAttack())
	{
		Begin_DoubleShot();
		DebugLog::Print("OnAttack");
	}
	else
	{
		if (Status->GetEnableCombo())
		{
			Status->SetComboAttack(true);
			DebugLog::Print("OnComboAttack");
		}
	}

}

void ACharacter_TwinBlast::OnWalkMode()
{
	GetCharacterMovement()->MaxWalkSpeed = Status->GetWalkSpeed();
}

void ACharacter_TwinBlast::OnJogMode()
{
	GetCharacterMovement()->MaxWalkSpeed = Status->GetRunSpeed();;
}

void ACharacter_TwinBlast::OnSprintMode()
{
	GetCharacterMovement()->MaxWalkSpeed = Status->GetSprintSpeed();
}

void ACharacter_TwinBlast::OnAvoid()
{
	//Animation->Dive_Forward();
}

void ACharacter_TwinBlast::OnAimMode()
{
	Status->SetAimMode(true);
	//bUseControllerRotationYaw = false;
	SpringArm->TargetArmLength = Status->GetAimModeArmLength();
}

void ACharacter_TwinBlast::OffAimMode()
{
	Status->SetAimMode(false);
	
	//bUseControllerRotationYaw = true;
	SpringArm->TargetArmLength = Status->GetBaseArmLength();
}

void ACharacter_TwinBlast::Begin_DoubleShot()
{
	Status->SetAttack(true);
	Animation->Attack_DoubleShot();
}


void ACharacter_TwinBlast::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
		case EStateType::Dive_Forward: Begin_Roll(); break;
		case EStateType::Dive_Backward: Begin_Roll(); break;
		case EStateType::Dive_Right: Begin_Roll(); break;
		case EStateType::Dive_Left: Begin_Roll(); break;
	}
}

void ACharacter_TwinBlast::Begin_Roll()
{
	State->SetIdleMode();
}

void ACharacter_TwinBlast::End_Roll()
{
}

