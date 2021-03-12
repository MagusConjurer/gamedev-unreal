// Copyright Cameron Davis 2021 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;

UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* ParticleTrail;
	
	// Variables
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType> DamageType;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 1300;
	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage = 50;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* HitParticle;
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* HitSound;
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* LaunchSound;
	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UCameraShake> HitShake;
	
	// Functions
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
