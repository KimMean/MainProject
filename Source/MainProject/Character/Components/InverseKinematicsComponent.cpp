#include "Character/Components/InverseKinematicsComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Gameframework/Character.h"
#include "Components/CapsuleComponent.h"

UInverseKinematicsComponent::UInverseKinematicsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UInverseKinematicsComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void UInverseKinematicsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Tick���� ������ ����
	float leftDistance;
	float rightDistance;
	FRotator leftRotation;
	FRotator rightRotation;
	Trace(LeftSocket, leftDistance, leftRotation);
	Trace(RightSocket, rightDistance, rightRotation);

	float offset = FMath::Min(leftDistance, rightDistance);
	Data.PelvisDistance.Z = UKismetMathLibrary::FInterpTo(Data.PelvisDistance.Z, offset, DeltaTime, InterpSpeed);
	// �̵� ����
	//Data.LeftDistance.Z = UKismetMathLibrary::FInterpTo(Data.LeftDistance.Z, (leftDistance - offset), DeltaTime, InterpSpeed);
	//Data.RightDistance.Z = UKismetMathLibrary::FInterpTo(Data.RightDistance.Z, -(rightDistance - offset), DeltaTime, InterpSpeed);
	Data.LeftDistance.Z = UKismetMathLibrary::FInterpTo(Data.LeftDistance.Z, leftDistance, DeltaTime, InterpSpeed);
	// ��Ī�̱� ������ -�� �ٲ����
	Data.RightDistance.Z = UKismetMathLibrary::FInterpTo(Data.RightDistance.Z, rightDistance, DeltaTime, InterpSpeed);

	Data.LeftRotation = UKismetMathLibrary::RInterpTo(Data.LeftRotation, leftRotation, DeltaTime, InterpSpeed);
	Data.RightRotation = UKismetMathLibrary::RInterpTo(Data.RightRotation, rightRotation, DeltaTime, InterpSpeed);
}

void UInverseKinematicsComponent::Trace(FName InSocket, float& OutDistance, FRotator& OutRotation)
{
	OutDistance = 0.0f;

	FVector location = OwnerCharacter->GetMesh()->GetSocketLocation(InSocket);
	FVector start = FVector(location.X, location.Y, OwnerCharacter->GetActorLocation().Z);

	float traceZ = start.Z - OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() - TraceDistance;
	FVector end = FVector(location.X, location.Y, traceZ);

	// �㸮���� �߹� ����������� ���

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(OwnerCharacter);

	FHitResult hitResult;

	UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, UEngineTypes::ConvertToTraceType(ECC_Visibility), true, ignoreActors, DrawDebugType, hitResult, true, FLinearColor::Green, FLinearColor::Red);

	if (!hitResult.IsValidBlockingHit()) return;

	// �浹�������� TraceEnd�� ���� �׸�ŭ �÷���
	float length = (hitResult.ImpactPoint - hitResult.TraceEnd).Size();
	// ���� ������ ����
	//OutDistance = OffsetDistance + length - TraceDistance;
	OutDistance = length - TraceDistance;

	// ��������, �̸� ���� ��, ��ġ ȸ���� ���� ��
	FVector normal = hitResult.ImpactNormal;
	float roll = UKismetMathLibrary::DegAtan2(normal.X, normal.Z);
	float pitch = -UKismetMathLibrary::DegAtan2(normal.Y, normal.Z);

	OutRotation = FRotator(pitch, 0.0f, roll);
}


