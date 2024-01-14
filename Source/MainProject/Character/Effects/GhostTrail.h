#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GhostTrail.generated.h"

class UPoseableMeshComponent;
class UMaterialInstance;

UCLASS()
class MAINPROJECT_API AGhostTrail : public AActor
{
	GENERATED_BODY()
	
public:	
	AGhostTrail();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public :
	void SetSkeletalMeshPose(USkeletalMeshComponent* InSkeletalMesh);

private :
	UPROPERTY(VisibleDefaultsOnly)
		UPoseableMeshComponent* PoseableMesh;

	UPROPERTY(VisibleDefaultsOnly)
		UMaterialInstance* GhostMaterial;

	TArray<UMaterialInstanceDynamic*> Materials;

	bool IsSpawned = false;
	float FadeCountDown;
	float FadeOutTime = 2.0f;

};
