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
#include "Character/Bullets/ChargeBolt.h"
#include "Character/Bullets/Grenade.h"
#include "Utilities/DebugLog.h"

ACharacter_TwinBlast::ACharacter_TwinBlast(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
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
	
	ConstructorHelpers::FClassFinder<ABullet> bullet(L"Blueprint'/Game/Characters/Bullets/BP_Bullet.BP_Bullet_C'");
	Bullet = bullet.Class;
	ConstructorHelpers::FClassFinder<AChargeBolt> chargeBolt(L"Blueprint'/Game/Characters/Bullets/BP_ChargeBolt.BP_ChargeBolt_C'");
	ChargeBolt = chargeBolt.Class;
	ConstructorHelpers::FClassFinder<AGrenade> grenade(L"Blueprint'/Game/Characters/Bullets/BP_Grenade.BP_Grenade_C'");
	Grenade = grenade.Class;
}

void ACharacter_TwinBlast::BeginPlay()
{
	Super::BeginPlay();

	//MainWidget = CreateWidget<UMainWidget, APlayerController>(GetController<APlayerController>(), //MainWidgetClass);
	//MainWidget->AddToViewport();
	//MainWidget->Set_WBP_HPBar_Percent(0.5f);

	State->OnStateTypeChanged.AddDynamic(this, &ACharacter_TwinBlast::OnStateTypeChanged);
	Status->OnActionModeChanged.AddDynamic(this, &ACharacter_TwinBlast::OnActionModeChanged);
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

	PlayerInputComponent->BindAction("UltimateMode", EInputEvent::IE_Pressed, this, &ACharacter_TwinBlast::OnUltimateMode);
	PlayerInputComponent->BindAction("UltimateMode", EInputEvent::IE_Released, this, &ACharacter_TwinBlast::OffUltimateMode);
	PlayerInputComponent->BindAction("ChargeBlastMode", EInputEvent::IE_Pressed, this, &ACharacter_TwinBlast::OnChargeBlastMode);
	PlayerInputComponent->BindAction("ChargeBlastMode", EInputEvent::IE_Released, this, &ACharacter_TwinBlast::OffChargeBlastMode);
	PlayerInputComponent->BindAction("GrenadeMode", EInputEvent::IE_Pressed, this, &ACharacter_TwinBlast::OnGrenadeMode);
	PlayerInputComponent->BindAction("GrenadeMode", EInputEvent::IE_Released, this, &ACharacter_TwinBlast::OffGrenadeMode);
}

void ACharacter_TwinBlast::Begin_DoubleCombo()
{
	if (!Status->GetComboAttack())
		return;

	Animation->Attack_DoubleShotCombo();
}

void ACharacter_TwinBlast::End_DoubleShot()
{
	Status->SetComboAttack(false);
	Status->SetAttack(false);
}

void ACharacter_TwinBlast::Firing(const USkeletalMeshSocket* InSocket)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.bDeferConstruction = true;
	

	FVector location = GetMesh()->GetSocketLocation(InSocket->SocketName);
	FRotator rotator;

	switch (Status->GetActionMode())
	{
	case EActionMode::NormalMode:
	case EActionMode::UltimateMode:
		BulletFire(location, rotator, SpawnParams);
		break;
	case EActionMode::ChargeBlastMode:
		ChargeBoltFire(location, rotator, SpawnParams);
		break;
	case EActionMode::GrenadeMode:
		GrenadeFire(location, rotator, SpawnParams);
		break;
	}
}

void ACharacter_TwinBlast::BulletFire(const FVector& InLocation, const FRotator& InRotator, const FActorSpawnParameters& InParam)
{
	ABullet* bullet = GetWorld()->SpawnActor<ABullet>(Bullet, InLocation, InRotator, InParam);
	if (bullet == nullptr) return;
	bullet->SetDirection(Camera->GetForwardVector());
	bullet->FinishSpawning(bullet->GetTransform());
}

void ACharacter_TwinBlast::ChargeBoltFire(const FVector& InLocation, const FRotator& InRotator, const FActorSpawnParameters& InParam)
{
	AChargeBolt* chargeBolt = GetWorld()->SpawnActor<AChargeBolt>(ChargeBolt, InLocation, InRotator, InParam);
	if (chargeBolt == nullptr) return;
	chargeBolt->SetDirection(Camera->GetForwardVector());
	chargeBolt->FinishSpawning(chargeBolt->GetTransform());
}

void ACharacter_TwinBlast::GrenadeFire(const FVector& InLocation, const FRotator& InRotator, const FActorSpawnParameters& InParam)
{
	AGrenade* grenade = GetWorld()->SpawnActor<AGrenade>(Grenade, InLocation, InRotator, InParam);
	if (grenade == nullptr) return;
	grenade->SetProjectileDirection(Camera->GetForwardVector());
	grenade->FinishSpawning(grenade->GetTransform());
}


void ACharacter_TwinBlast::EndAttackMode()
{
	Status->SetAttack(false);
	Status->SetAimMode(false);
	SpringArm->TargetArmLength = Status->GetBaseArmLength();
	Status->ChangeActionMode(EActionMode::NormalMode);
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
	switch (Status->GetActionMode())
	{
		case EActionMode::NormalMode :
			Attack_DoubleShot();
			break;
		case EActionMode::UltimateMode:
			Attack_Ultimate();
			break;
		case EActionMode::ChargeBlastMode:
			Attack_ChargeBlast();
			break;
		case EActionMode::GrenadeMode:
			Attack_Grenade();
			break;
	}
	Status->SetAttack(true);
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

void ACharacter_TwinBlast::OnNormalMode()
{
	Status->ChangeActionMode(EActionMode::NormalMode);
}

void ACharacter_TwinBlast::OffNormalMode()
{
}

void ACharacter_TwinBlast::OnUltimateMode()
{
	if (Status->GetAttack()) return;

	Status->SetAimMode(true);

	SpringArm->TargetArmLength = Status->GetAimModeArmLength();
	Status->ChangeActionMode(EActionMode::UltimateMode);
	Animation->Attack_UltimateMode();
}

void ACharacter_TwinBlast::OffUltimateMode()
{
}

void ACharacter_TwinBlast::OnChargeBlastMode()
{
	if (Status->GetAttack()) return;

	Animation->Attack_ChargeBlastMode();
	Status->ChangeActionMode(EActionMode::ChargeBlastMode);
}

void ACharacter_TwinBlast::OffChargeBlastMode()
{

}

void ACharacter_TwinBlast::OnGrenadeMode()
{
	if (Status->GetAttack()) return;

	Animation->Attack_GrenadeMode();
	Status->ChangeActionMode(EActionMode::GrenadeMode);
}

void ACharacter_TwinBlast::OffGrenadeMode()
{
}

void ACharacter_TwinBlast::Attack_DoubleShot()
{
	if (!Status->GetAttack())
	{
		Animation->Attack_DoubleShot();
	}
	else
	{
		if (Status->GetEnableCombo())
		{
			Status->SetComboAttack(true);
		}
	}
}

void ACharacter_TwinBlast::Attack_Ultimate()
{
	if (Status->GetAttack()) return;

	Animation->Attack_Ultimate();
}

void ACharacter_TwinBlast::Attack_ChargeBlast()
{
	if (Status->GetAttack()) return;

	Animation->Attack_ChargeBlast();
}

void ACharacter_TwinBlast::Attack_Grenade()
{
	if (Status->GetAttack()) return;

	Animation->Attack_Grenade();
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

void ACharacter_TwinBlast::OnActionModeChanged(EActionMode InPrevType, EActionMode InNewType)
{
}

void ACharacter_TwinBlast::Begin_Roll()
{
	State->SetIdleMode();
}

void ACharacter_TwinBlast::End_Roll()
{
}

