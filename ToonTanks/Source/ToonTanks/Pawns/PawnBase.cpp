// Copyright Cameron Davis 2021 All Rights Reserved


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "ToonTanks/Actors/ProjectileBase.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

// Update rotation to look at the targets location
void APawnBase::RotateTurret(FVector Target)
{
	FVector TargetClean = FVector(Target.X, Target.Y, TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = TurretMesh->GetComponentLocation();

	FRotator TurretRotation = FVector(TargetClean - StartLocation).Rotation();

	TurretMesh->SetWorldRotation(TurretRotation);
}

// Create projectile and launch at target
void APawnBase::Fire()
{
	if (ProjectileClass)
	{
		// Get spawn location and rotation
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

		// Spawn projectile at the location and fire towards the rotation
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
		TempProjectile->SetOwner(this);
	}
}

// Play effects and handle destruction of pawn
void APawnBase::HandleDestruction()
{
	// Base Function
	// Play death effects, sound, and camera shake

	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());

	// Child Overrides 
	// PawnTurret -- update GameMode and then destory self
	// Pawn Tank -- update GameMode and then hide components/stop movement
}

