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
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType> DamageType;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 1300;
	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage = 50;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
