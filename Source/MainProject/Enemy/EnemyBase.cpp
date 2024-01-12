#include "Enemy/EnemyBase.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"

#include "Enemy/Components/EnemyStatusComponent.h"
#include "Enemy/Components/EnemyAnimComponent.h"
#include "Enemy/Widgets/EnemyHelthPoint.h"
#include "Enemy/Widgets/EnemyNameTag.h"

#include "Utilities/DebugLog.h"
AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(FName("Enemy"));

	State = CreateDefaultSubobject<UEnemyStateComponent>(TEXT("StateComponent"));
	Status = CreateDefaultSubobject<UEnemyStatusComponent>(TEXT("StatusComponent"));
	Animation = CreateDefaultSubobject<UEnemyAnimComponent>(TEXT("AnimationComponent"));

	NameTagWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("NameTagWidget"));
	HPWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HelthWidget"));
	NameTagWidget->SetupAttachment(GetMesh());
	HPWidget->SetupAttachment(GetMesh());

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));

	ConstructorHelpers::FClassFinder<UEnemyNameTag> nameWidget(L"WidgetBlueprint'/Game/Enemies/Widgets/WB_EnemyNameTag.WB_EnemyNameTag_C'");
	NameTagWidget->SetWidgetClass(nameWidget.Class);
	NameTagWidget->SetWidgetSpace(EWidgetSpace::World);
	NameTagWidget->SetRelativeLocation(FVector(0, 0, 240));
	NameTagWidget->SetDrawSize(FVector2D(150, 20));

	ConstructorHelpers::FClassFinder<UEnemyHelthPoint> hpWidget(L"WidgetBlueprint'/Game/Enemies/Widgets/WB_EnemyHelthPoint.WB_EnemyHelthPoint_C'");
	HPWidget->SetWidgetClass(hpWidget.Class);
	HPWidget->SetWidgetSpace(EWidgetSpace::World);
	HPWidget->SetRelativeLocation(FVector(0, 0, 220));
	HPWidget->SetDrawSize(FVector2D(150, 15));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	InitStatus();
	InitWidgets();
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector cameraLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransform().GetLocation();

	FVector hpLocation = HPWidget->K2_GetComponentLocation();
	FVector nameLocation = NameTagWidget->K2_GetComponentLocation();

	FRotator hpRotator = UKismetMathLibrary::FindLookAtRotation(hpLocation, cameraLocation);
	FRotator nameRotator = UKismetMathLibrary::FindLookAtRotation(nameLocation, cameraLocation);

	HPWidget->SetWorldRotation(hpRotator);
	NameTagWidget->SetWorldRotation(nameRotator);
}

float AEnemyBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	State->SetIdleMode();

	Status->AdjustHealthPoint(-Damage);
	Status->SetIsHitted(true);

	UpdateHealthPoint();

	if (Status->GetHealthPoint() == 0)
		State->SetDeathMode();

	return Damage;
}

UEnemyStateComponent* AEnemyBase::GetStateComponent()
{
	return State;
}

void AEnemyBase::Attack()
{
	return;
}

void AEnemyBase::Death()
{
	Destroy();
}

void AEnemyBase::SetNameTag(FString InName)
{
	Cast<UEnemyNameTag>(NameTagWidget->GetUserWidgetObject())->SetNameTag(FText::FromString(InName));
}

void AEnemyBase::UpdateHealthPoint()
{
	Cast<UEnemyHelthPoint>(HPWidget->GetUserWidgetObject())->Set_HelthPoint_Percent(Status->GetHealthPoint(), Status->GetMaxHealthPoint());
}

void AEnemyBase::InitStatus()
{
	Status->SetHealthPoint(Status->GetMaxHealthPoint());
}

void AEnemyBase::InitWidgets()
{
	NameTagWidget->InitWidget();
	HPWidget->InitWidget();
}


