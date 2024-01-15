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

	// Tick에서 간격을 구함
	float leftDistance;
	float rightDistance;
	FRotator leftRotation;
	FRotator rightRotation;
	Trace(LeftSocket, leftDistance, leftRotation);
	Trace(RightSocket, rightDistance, rightRotation);

	float offset = FMath::Min(leftDistance, rightDistance);
	Data.PelvisDistance.Z = UKismetMathLibrary::FInterpTo(Data.PelvisDistance.Z, offset, DeltaTime, InterpSpeed);
	// 이동 보간
	//Data.LeftDistance.Z = UKismetMathLibrary::FInterpTo(Data.LeftDistance.Z, (leftDistance - offset), DeltaTime, InterpSpeed);
	//Data.RightDistance.Z = UKismetMathLibrary::FInterpTo(Data.RightDistance.Z, -(rightDistance - offset), DeltaTime, InterpSpeed);
	Data.LeftDistance.Z = UKismetMathLibrary::FInterpTo(Data.LeftDistance.Z, leftDistance, DeltaTime, InterpSpeed);
	// 대칭이기 때문에 -로 바꿔야함
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

	// 허리에서 발밑 어느정도까지 계산

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(OwnerCharacter);

	FHitResult hitResult;

	UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, UEngineTypes::ConvertToTraceType(ECC_Visibility), true, ignoreActors, DrawDebugType, hitResult, true, FLinearColor::Green, FLinearColor::Red);

	if (!hitResult.IsValidBlockingHit()) return;

	// 충돌지점에서 TraceEnd를 빼서 그만큼 올려줌
	float length = (hitResult.ImpactPoint - hitResult.TraceEnd).Size();
	// 발이 움직일 지점
	//OutDistance = OffsetDistance + length - TraceDistance;
	OutDistance = length - TraceDistance;

	// 수직벡터, 이를 통해 롤, 피치 회전을 얻을 것
	FVector normal = hitResult.ImpactNormal;
	float roll = UKismetMathLibrary::DegAtan2(normal.X, normal.Z);
	float pitch = -UKismetMathLibrary::DegAtan2(normal.Y, normal.Z);

	OutRotation = FRotator(pitch, 0.0f, roll);
}


