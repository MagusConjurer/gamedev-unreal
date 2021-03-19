// Copyright Cameron Davis 2021. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// Components
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere)
	UParticleSystem* BulletImpact;
	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;
	UPROPERTY(EditAnywhere)
	USoundBase* BulletImpactSound;

	// Variables
	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;
	UPROPERTY(EditAnywhere)
	float Damage = 10;

	//Functions

	// Get the owning pawn and it's controller
	AController* GetOwnerController() const;

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);
};
