#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy_Sword.generated.h"


UCLASS()
class MAINPROJECT_API AEnemy_Sword : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemy_Sword();

protected:
	virtual void BeginPlay() override;

public :
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


private :
	UPROPERTY(VisibleDefaultsOnly)
		USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* BoxCollision;
};
