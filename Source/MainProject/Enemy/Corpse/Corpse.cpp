#include "Enemy/Corpse/Corpse.h"

#include "Engine/SkeletalMeshSocket.h"
#include "Components/WidgetComponent.h"
#include "Enemy/Weapons/Enemy_Sword.h"
#include "Enemy/Components/EnemyStatusComponent.h"
#include "Enemy/Components/EnemyAnimComponent.h"
#include "Enemy/Widgets/EnemyHelthPoint.h"
#include "Enemy/Widgets/EnemyNameTag.h"
#include "Abilities/DamageType/DamageBase.h"

#include "Utilities/DebugLog.h"

ACorpse::ACorpse()
{

	State = CreateDefaultSubobject<UEnemyStateComponent>(TEXT("StateComponent"));
	Status = CreateDefaultSubobject<UEnemyStatusComponent>(TEXT("StatusComponent"));
	Animation = CreateDefaultSubobject<UEnemyAnimComponent>(TEXT("AnimationComponent"));

	NameTagWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("NameTagWidget"));
	HPWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HelthWidget"));
	NameTagWidget->SetupAttachment(GetMesh());
	HPWidget->SetupAttachment(GetMesh());

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/CityofBrass_Enemies/Meshes/Enemy/Corpse/Corpse_Sword.Corpse_Sword'");
	GetMesh()->SetSkeletalMesh(mesh.Object);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));

	ConstructorHelpers::FClassFinder<UEnemyNameTag> nameWidget(L"WidgetBlueprint'/Game/Enemies/Widgets/WB_EnemyNameTag.WB_EnemyNameTag_C'");
	NameTagWidget->SetWidgetClass(nameWidget.Class);
	NameTagWidget->SetWidgetSpace(EWidgetSpace::Screen);
	NameTagWidget->SetRelativeLocation(FVector(0, 0, 240));
	NameTagWidget->SetDrawSize(FVector2D(150, 20));

	ConstructorHelpers::FClassFinder<UEnemyHelthPoint> hpWidget(L"WidgetBlueprint'/Game/Enemies/Widgets/WB_EnemyHelthPoint.WB_EnemyHelthPoint_C'");
	HPWidget->SetWidgetClass(hpWidget.Class);
	HPWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HPWidget->SetRelativeLocation(FVector(0, 0, 220));
	HPWidget->SetDrawSize(FVector2D(150, 15));

}

void ACorpse::BeginPlay()
{
	Super::BeginPlay();

	Sword = GetWorld()->SpawnActor<AEnemy_Sword>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (Sword)
	{
		const USkeletalMeshSocket* socket = GetMesh()->GetSocketByName("SwordSocket");
		socket->AttachActor(Sword, GetMesh());
	}

	State->OnEnemyStateTypeChanged.AddDynamic(this, &ACorpse::OnEnemyStateTypeChanged);

	Status->SetHelthPoint(Status->GetMaxHelthPoint());

	NameTagWidget->InitWidget();
	HPWidget->InitWidget();

	Cast<UEnemyNameTag>(NameTagWidget->GetUserWidgetObject())->SetNameTag(FText::FromString("Corpse"));
	Cast<UEnemyHelthPoint>(HPWidget->GetUserWidgetObject())->Set_HelthPoint_Percent(Status->GetHelthPoint(), Status->GetMaxHelthPoint());
}

void ACorpse::Death()
{
	Sword->Destroy();
	Destroy();
}

float ACorpse::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Status->AdjustHelthPoint(-DamageAmount);

	Cast<UEnemyHelthPoint>(HPWidget->GetUserWidgetObject())->Set_HelthPoint_Percent(Status->GetHelthPoint(), Status->GetMaxHelthPoint());
	
	if (Status->GetHelthPoint() == 0)
		State->SetDeathMode();

	UDamageBase* damageType = Cast<UDamageBase>(DamageEvent.DamageTypeClass->GetDefaultObject());

	if (damageType)
	{
		switch (damageType->GetDamageType())
		{
			case FDamageType::KnockBack :
				State->SetHittedMode();
				// 타겟설정
				// 뒤로 밀려나는 애니메이션
				// 넉백
				float power = damageType->GetKnockBackPower();
				DebugLog::Print(GetActorForwardVector() * 1000);
				LaunchCharacter(GetActorForwardVector() * 1000, false, false);
				break;
		}
	}

	return DamageAmount;
}

void ACorpse::OnEnemyStateTypeChanged(EEnemyStateType InPrevType, EEnemyStateType InNewType)
{
	switch (InNewType)
	{
	case EEnemyStateType::Idle:	break;
	case EEnemyStateType::Approach: break;
	case EEnemyStateType::Action: break;
	case EEnemyStateType::Patrol: break;
	case EEnemyStateType::Hitted: break;
	case EEnemyStateType::Stunned: break;
	case EEnemyStateType::Avoid: break;
	case EEnemyStateType::Death: break;
	case EEnemyStateType::Max: break;
	default: break;
	}
}

